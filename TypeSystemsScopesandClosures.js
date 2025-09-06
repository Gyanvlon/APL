function makeCounter() {
    let count = 0;
    function counter() {
        count += 1;
        return count;
    }
    return counter;
}

const counter1 = makeCounter();
console.log(counter1());
console.log(counter1()); 