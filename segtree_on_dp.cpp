for _ in range(int(input())):
    n=int(input())
    if n<=9:
        print(-1)
        continue
    
    if n%2==0:
        a=2
        
        n-=2
        if (n//2)%2==0:
            b=n//2 - 1
            c= n-a-b+2
        else:
            b=n//2 - 2
            c= n-a-b+2
        print(*list(sorted([a,b,c])))
    else:
        cnt=0
        a=-1
        b=-1
        c=-1
        for i in range(65, -1, -1):
            if n&(1<<i):
                cnt+=1
                if b==-1:
                    b=1<<i
                elif c==-1:
                    c=1<<i
                else:
                    if a==-1:
                        a=n-b-c
                    
        if cnt<=3:
            print(-1)
        else:
            print(*list(sorted([a,b,c])))