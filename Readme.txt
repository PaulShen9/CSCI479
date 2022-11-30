This is Paul Shen's assignment 4 readme. In this file, I will answer the question in the requriment and talk out my design.

1:How to compile and execute your program? 
There is a makefile placed in the same direcotry. Type make to compile the program. If you want to unintall the program, just type make clean.
Type ./assignment4 to execute the program. The program will automaticlly enter several pairs into the KB, and than it will ask user to choose their opinion. See part 7 for more detail.

2:Explain the concrete data structures used to implement your knowledge base and the reason why you choose these particular data structures.
In this assignment, I use hash table as my main data structure.The reason I pick hash table is because in this assgienment, we can consider each pair has a key(conclution,for example: A) and value(a sentence to reach the conclution, for example: !A^B). At the begining of the development, I tried use two arraies who shared the index but I found out it is too complex, so I change the data structure to the hash table. 
Also, I used list as a sub data structure. The main reason I have to use list is becasue for the value part, most time it does not only has one elmenet. For the most time, it is in the previous example formation. So I have to split them(see part 7) and consider them as a list.


3:Identify the inference rule(s) used by your AI agent and the algorithm used to realize the inference rule(s).
The rule I used for this assignment is !A^B has the opposite result with A^!B. I use this rule as base to build the whole program.

4:Analyse the algorithm used for ASK method to prove that it runs in linear time to the size of the knowledge base.
In the ASK method, the algorithm I used is backward channing. The way I impltment the backward channing is use a recurrsive call. 
For example, if we have:
C=>D
A^B => C
A
B
The step will becomes
1: I need C for D
2: 1 need A for C
4: A check
3: I need B for C.
5: B check
6  A^B check
7: C check
8: D check
9: Done.
The reason it is runs in liner time is because it will viste each node for only one times, so the running time is liner base on the size of the KB(See part 7 for more).

5:Any known bugs;
Nothing for known. But the program only has few input checking. 

6: Resource/Technology used for the assignment
For the resource, mostlly google, wiki , youtube vedio and lecture notes. 
For the technology, I used some of the build in function(like push, strcpy) to support the work.

7: Detailed discussion of my program.
The program will first automatically add some pairs into the KB. After that, the program will ask user to enter their opinion. There will be three opinion for the user. They are End for end, Ask for ask information from the database and tell to tell the information to the database.
For the tell opinion, it will ask user to enter a key and a pair as userinput to build the
pair.Once the information is entered, the program will use make_pair to pair the input and
called the insert function to insert the pair into the hash table.The insert function will first
check the key is empty or not. If it is empty which means user enter wrong information, then it
will return with an error message. If it goes through, the program will check the key is a
negation(for example !A) or not. If it is a negation, it will remove the negation sign and used
the method which mentioned in the part3 to get rid of the negation. In this step, the program
will used a helper function called split to help to build the list. After this step, it will
test the value of the input. If the input is "", it means the key part of this pair will always
be ture. By using the same method before, I will set the value to always or never based does the
key contain a negation sign or not. If it contains a negation sign, then it should be always be
false, so I set the value of this key to never. Same logic for the always. Once this step is
finished, then no more test is needed. I just add the data into the hash table and increase the
counter. After this step, the insert should be finished.
For the ask opinion, it will ask user to enter a key as its input and use this key to go through
the KB to find out does the KB has it or not.Same as logic before, I will remove the negation
sign from the start and put them into different cases. Then the key will go to another function.
In this function, it will first check wheather the key is ""or not. The way I keep track the key
is valid or not and does the result is found or not is to use a muplitcation. At failure
condition(not found,not valid), the return value will beccome 0, so the muplity result will
always become 0. By using this way, I can keep track the result with low cost. If the key is
valid(found), then I will pass the value(list) of this key to function and do a recurr call on
this list to go through all the list element in this list. At this point, I used the backword
cahnning algothrism as mentioned in the part 4. The reason it runs in a liner time is because I
will first go through the whole hash table to find out the position that hold the key. Next, I
will go through the value of this key and do the same as above. It is pretty much a depth-first
search according to my drawing, goes to the left end most and then go to the next, then next.So, the running time should be liner base on the size of the KB. If the final result is not found, the function will return 0
and tell the user it is not included in the KB, eitherwise, it will tell it is included.
