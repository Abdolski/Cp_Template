for _ in range(int(input())):
    n=int(input())
    if n<=9 or n==11:
        print(-1)
        continue
    
    if n%2==0:
        print(2,3,n-5)
    else:
        
        if (n-3)%3==1:
            
            if n-8==5:
                print(-1)
            else:
                print(3,5,n-8)
        else:
            if n-7==4:
                print(-1)
            else:
                print(3,4,n-7)