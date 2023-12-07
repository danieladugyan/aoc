import { readFileSync } from 'fs';

const file = readFileSync("./input.txt", "utf-8");
const data = file.split("\n");

const seeds = data.splice(0, 1)[0].split(" ").slice(1).map(Number);
console.log(seeds);