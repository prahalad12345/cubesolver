import kociemba

f=open('input.txt','r')
s=f.read() 
f.close() 
print(s)
solution=kociemba.solve(s)
print(solution)
f=open('output.txt','w')
f.write(solution)
f.close() 

