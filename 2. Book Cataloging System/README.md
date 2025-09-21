# Book Cataloging System (Ruby + Sinatra)

A simple GUI (web) application to manage a catalog of books:
- Add and remove books
- Search by title/author/genre
- Reports by genre and by author
- JSON file storage (no database required)

## Why Ruby here?

Ruby’s dynamic typing and rich `Enumerable` API make it easy to filter, group, and transform data:
we use blocks (`select`, `group_by`, `map`, `sort_by`) extensively to implement search and reports.

## Prerequisites (macOS)

1. Install Homebrew:
   ```bash
   /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
   eval "$(/opt/homebrew/bin/brew shellenv)"
   ```
2. Install rbenv + Ruby:

```bash
brew install rbenv ruby-build
echo 'eval "$(rbenv init - zsh)"' >> ~/.zshrc
source ~/.zshrc
rbenv install 3.3.4
rbenv global 3.3.4
ruby -v
```

3. VS Code extension: Ruby LSP.

4. Install & Run
```bash
cd rubyBookCatalogApp/bookcatalogapp
bundle install
ruby app.rb
```
Open your browser at http://localhost:4567.

Tip: auto-reload in development:

```bash
rerun "ruby app.rb"
```
## Storage

- Book data are stored in data/books.json as an array of objects:

```
[
  {
    "id": "uuid",
    "title": "The Hobbit",
    "author": "J.R.R. Tolkien",
    "genre": "Fantasy",
    "year": 1937
  }
  ...
]
```

The file is created automatically if missing.

## Features

1. Add a book: Add Book form (Title, Author, Genre, Year)
2. Remove a book: click Delete in the table
3. Search: by Title, Author, or Genre (case-insensitive)
4. Reports:
   - By Genre: groups all books by genre
   - By Author: groups all books by author
5. Implementation details:
    - Data loading/saving uses JSON and file locks (File.flock) for basic safety
    - Ruby’s group_by + blocks power the reporting views
    - Minimal CSS under public/styles.css


## Notes

- This app uses just Ruby’s standard tools and Sinatra—no database setup.
- If you prefer persistence across machines, keep data/books.json in your repo.

## Collaborators

- Ajal RC  
- Laxmi Oruganti  
- Gyan Bahadur Tamang