function solution(n,a,b)
{
    var answer = 1;
    
    while(true){
        if(Math.abs(a - b) == 1){            
            if(a % 2 == 0 && b == a - 1 || b % 2 == 0 && a == b - 1){
                break;
            }
        }
        if(a % 2){
            a = (a + 1) / 2;
        }
        else{
            a /= 2;
        }
        if(b % 2){
            b = (b + 1) / 2;
        }
        else{
            b /= 2; 
        }
        answer++;
    }
    
    return answer;
}