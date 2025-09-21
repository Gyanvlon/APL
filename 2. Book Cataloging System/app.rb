
require "sinatra"
require "json"
require "securerandom"
require "fileutils"


set :bind, "0.0.0.0"   # allow LAN access if needed
set :port, 4567
set :server, :puma

DATA_DIR  = File.join(__dir__, "data")
DB_FILE   = File.join(DATA_DIR, "books.json")

# Ensure data directory and file exist
FileUtils.mkdir_p(DATA_DIR)
unless File.exist?(DB_FILE)
  File.write(DB_FILE, JSON.pretty_generate([]))
end

# --- Helpers: load/save the "database" (a JSON file) ---
def load_books
  # Read and parse JSON; if file empty or invalid, return empty array
  raw = File.read(DB_FILE)
  JSON.parse(raw, symbolize_names: true)
rescue JSON::ParserError
  []
end

def save_books(books)
  # Write atomically with file lock to avoid corruption on concurrent writes
  File.open(DB_FILE, "w") do |f|
    f.flock(File::LOCK_EX)
    f.write(JSON.pretty_generate(books))
    f.flock(File::LOCK_UN)
  end
end

# --- Validate a single book payload from form params ---
def build_book_from_params(params)
  # Ruby lets us treat params (strings) flexibly; we normalize safely:
  title = params["title"].to_s.strip
  author = params["author"].to_s.strip
  genre = params["genre"].to_s.strip
  year_str = params["year"].to_s.strip

  halt 400, "Title is required"  if title.empty?
  halt 400, "Author is required" if author.empty?
  halt 400, "Genre is required"  if genre.empty?

  # Year is optional but if provided, ensure integer-like
  year = year_str.empty? ? nil : Integer(year_str) rescue halt(400, "Year must be a number")

  {
    id: SecureRandom.uuid,
    title: title,
    author: author,
    genre: genre,
    year: year
  }
end

# --- Views helpers available in templates ---
helpers do
  def h(text)
    # Simple HTML escape for safe output
    Rack::Utils.escape_html(text.to_s)
  end

  def nav_link(name, path)
    %(<a href="#{path}">#{h(name)}</a>)
  end
end

# --- Routes ---

# Home: quick links + counts
get "/" do
  @books = load_books
  erb :index
end

# List all books
get "/books" do
  @books = load_books.sort_by { |b| b[:title].downcase }
  erb :books
end

# Show "add book" form
get "/books/new" do
  erb :new_book
end

# Create book
post "/books" do
  books = load_books
  book  = build_book_from_params(params)
  books << book
  save_books(books)
  redirect "/books"
end

# Remove book by id
post "/books/:id/delete" do
  id = params[:id]
  books = load_books
  before = books.size
  books.reject! { |b| b[:id] == id }
  save_books(books)
  redirect "/books?removed=#{(before - books.size) > 0}"
end

# Search form
get "/search" do
  erb :search
end

# Search results
get "/search/results" do
  @q     = params["q"].to_s.strip
  @field = params["field"].to_s.strip            # "title" | "author" | "genre"
  halt 400, "Search term is required." if @q.empty?
  halt 400, "Invalid field." unless %w[title author genre].include?(@field)

  books = load_books
  # Case-insensitive substring match using Ruby’s Enumerable + blocks
  @results = books.select do |b|
    value = b[@field.to_sym].to_s.downcase
    value.include?(@q.downcase)
  end
  erb :results
end

# Reports: by genre
get "/reports/genre" do
  books = load_books
  # group_by returns a Hash{ genre => [books...] }
  @by_genre = books.group_by { |b| (b[:genre] || "").downcase }
                   .transform_keys { |g| g.empty? ? "(unknown)" : g }
                   .sort_by { |genre, arr| [genre, arr.size] }
  erb :report_genre
end

# Reports: by author
get "/reports/author" do
  books = load_books
  @by_author = books.group_by { |b| (b[:author] || "").downcase }
                    .transform_keys { |a| a.empty? ? "(unknown)" : a }
                    .sort_by { |author, arr| [author, arr.size] }
  erb :report_author
end
