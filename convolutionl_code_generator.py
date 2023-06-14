def xor(a,b,c,d):
    if (a+b+c+d)%2==1:
        return 1
    else:
        return 0
def return_convoluted(lis):
    if len(lis)<7:
        print ("The size of the list is less than the length of the convolutional encoder")
        raise Exception
    arr=lis[0:7]
    print ("This is for debugging purposes only")
    print (arr)
    list=[]
    for i in range (7,len(lis)):   
        list.append(xor(arr[0],arr[1],arr[2],arr[3]))
        list.append(xor(arr[0],arr[2],arr[3],arr[5]))
        for j in range(6):
            arr[j]=arr[j+1]
        arr[6]=lis[i]
    for i in range (7):
        list.append(xor(arr[0],arr[1],arr[2],arr[3]))
        list.append(xor(arr[0],arr[2],arr[3],arr[5]))
        for j in range(6):
            arr[j]=arr[j+1]
        arr[6]=0
    return list
temparray=[1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1]
revarray=[]
for i in range(1,len(temparray)+1):
    revarray.append(temparray[-i])
temparray+=temparray
temparray+=revarray
temparray+=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
arr=(return_convoluted(temparray))

strin=""
for i in arr:
    if i==0:
        strin=strin+"00"
    else :
        strin=strin+"11"  

print(strin[0:32])
print(strin[32:64])
print(strin[64:96])
print(strin[96:128])
print(strin[128+0:128+32])
print(strin[128+32:128+64])
print(strin[128+64:128+96])
print(strin[128+96:128+128])
print(strin[256+0:256+32])
print(strin[256+32:256+64])
print(strin[256+64:256+96])
print(strin[256+96:256+128])
print(strin[384+0:384+32])
print(strin[384+32:384+64])
print(strin[384+64:384+96])
print(strin[384+96:384+128])
print(strin[512+0:512+32])
print(strin[512+32:512+64])
print(strin[512+64:512+96])
print(strin[512+96:512+128])
print(strin[640+0:640+32])
print(strin[640+32:640+64])
print(strin[640+64:640+96])
print(strin[640+96:640+128])
print(strin[768+0:768+32])
print(strin[768+32:768+64])
print(strin[768+64:768+96])
print(strin[768+96:768+128])


