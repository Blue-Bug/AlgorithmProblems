class Queue {
    constructor() {
        this._arr = [];
    }
    enqueue(item) {
        this._arr.push(item);
    }
    dequeue() {
        return this._arr.shift();
    }
    empty(){
        return this._arr.length == 0;
    }
}

let dir =  [[0,1],[1,0],[-1,0],[0,-1]];

function bfs(maps){
    let n = maps.length;
    let m = maps[0].length;
    let q = new Queue();
    let check = new Array(n);
    for(let i = 0; i < n; i++){
        check[i] = new Array(m);
        for(let j = 0; j < m; j++){
            check[i][j] = false;
        }
    }
    q.enqueue([0,0,1]);
    while(!q.empty()){
        let cur = q.dequeue();
        
        if(cur[0] == n-1 && cur[1] == m-1){
            return cur[2];
        }
        if(check[cur[0]][cur[1]])continue;
        check[cur[0]][cur[1]] = true;
        
        for(let i = 0; i < 4; i++){
            let nextRow = cur[0] + dir[i][0];
            let nextCol = cur[1] + dir[i][1];
            if(nextRow < 0 || nextRow >= n) continue;
            if(nextCol < 0 || nextCol >= m) continue;
            if(maps[nextRow][nextCol] != 0){
                q.enqueue([nextRow,nextCol,cur[2]+1]);
            }
        }
    }
    return -1;
}

function solution(maps) {
    var answer = 0;
    answer = bfs(maps);
    return answer;
}