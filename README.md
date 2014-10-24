MSS - Maximizing Satisfaction Scheduler
===

Maximizer of satisfaction scheduler. Made for PET-Informática UFPE for scheduling different groups of people to different classes based on their satisfaction in lecturing those classes.

The program must run in the same folder as a file named "Capadecide.txt", which must contain the following data:

<--------- Ignore this line, begin with the following line --------->
```
			MODULE_1	MODULE_2	...	MODULE_N
STUDENT_1	GRADE_1_1	GRADE_1_2	...	GRADE_1_N
STUDENT_2	GRADE_2_1	GRADE_2_2	...	GRADE_2_N
...			...			...				...
STUDENT_N	GRADE_N_1	GRADE_N_2	...	GRADE_N_N
***
MODULE_1	SIZE_OF_MODULE_1
MODULE_2	SIZE_OF_MODULE_2
...
MODULE_N	SIZE_OF_MODULE_N
***
STUDENT_X STUDENT_Y STRENGHT_OF_FRIENDSHIP_X_Y
STUDENT_Z STUDENT_K STRENGHT_OF_FRIENDSHIP_Z_K
***
```
<--------- Ignore this line, entry data ends here --------->

Each grade a student gives to a module must be an integer between 0 and 10. The program uses the square of the grade to maximize the efficience in the result.
Each strenght of friendship must be an integer in the range [-100,100] inclusive.
This program runs with a dynamic programming technique which uses a bitmask which size is equal to the number of students in the group. Therefore, the avarage complexity of the algorithm is O((2^Number_of_Members) * Number_of_Modules). With further analysis, one can prove
that this problem actually has a polynomial solution using flow networks. Anyone is welcome to change the approach.

Please, do not run this program for more than 16 students or more than 16 modules!
