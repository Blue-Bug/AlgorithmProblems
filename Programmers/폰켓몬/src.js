function solution(nums) {
    var answer = 0;
    var selNum = nums.length/2;
    var mySet = new Set();
    nums.forEach((a) =>{ mySet.add(a); });

    if(mySet.size >= selNum){
        answer = selNum;
    }
    else{
        answer = mySet.size;
    }
    return answer;
}