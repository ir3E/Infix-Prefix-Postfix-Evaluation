//BSIT 2-5 -- Group 1 Members: Balaca, Bonayog, Castillo, Cornelia, Jao, Sampaga, Taer, Velasco, Watson
//Data Structures & Algorithms (QUIZ #2) -- Prof. Lydinar Dastas

//header files  
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <unistd.h>  //for the sleep function

#define n 50  //constant variable 'n' --> size for array of the expressions

//global variables
int numbers[50], topN = -1, topO = -1;
char op[50];

//declaration of functions
void Infix();
int InEval(int numbers[50], char op[50]);
void Prefix();
int PreEval(int numbers[50], char op[50]);
void Postfix();
int PostEval(int numbers[50], char op[50]);
void push_num(int a);
void push_op(char ch);
int pop_num();
char pop_op();
int is_operator(char ch);
int priority(char ch);
void emptyNumStack();
void emptyOpeStack();

int main(){  //main program
	int menu, ch, x;
	
	printf("\n\n\t\t=========================================================");
	printf("\n\t\t\t\t Polish Notation Evaluation");
	printf("\n\t\t========================================================="); 
	printf("\n\n\t\t Hello! Welcome to our program.");
	printf("\n\n\t\t Please take note of the following before proceeding:");
	printf("\n\t\t   1.) Our program only accepts digits from 0-9.");
	printf("\n\t\t         > We cannot allow double digits (e.g. 11, 27).");
	printf("\n\n\t\t   2.) Our program only accepts the following operators:");
	printf("\n\t\t         > Multiplication sign (*)");
	printf("\n\t\t         > Division sign (/)");
	printf("\n\t\t         > Addition sign (+)");
	printf("\n\t\t         > Subtraction sign (-)");
	printf("\n\n\t\t Thank you for taking the time to read our instructions!");
	printf("\n\n\t\t  To continue, kindly press any key.");
	getch();
	printf("\n\n\t\t  Starting, please wait . . .");
	sleep(3);
	system("cls");
	
	do{
		printf("\n\n\t\t=====================");
		printf("\n\t\t     Menu Program");
		printf("\n\t\t=====================");
		printf("\n\n\t\t  [1] Infix");
		printf("\n\t\t  [2] Prefix");
		printf("\n\t\t  [3] Postfix");
		printf("\n\t\t  [4] EXIT");
		printf("\n\n\t\tPlease select a number: ");
		scanf("%d", &ch);
		system("cls");
		
		switch(ch){
			case 1:{
				printf("\n\n\t\t======================");
				printf("\n\t\t   INFIX EVALUATION");
				Infix();  //function call
				break;
			}
			case 2:{
				printf("\n\n\t\t======================");
				printf("\n\t\t  PREFIX EVALUATION");
				Prefix();  //function call
				break;
			}
			case 3:{
				printf("\n\n\t\t======================");
				printf("\n\t\t  POSTFIX EVALUATION");
				Postfix();  //function call
				break;
			}
			case 4:{
				printf("\n\n\t\t===========================================================");
				printf("\n\n\t\t  Are you sure you want to exit? (1 for YES, 0 for NO): ");
				scanf("%d", &x);
				
				if(x == 1){
					menu = 4;
					printf("\n\n\t\t  Please wait, proceeding to exit . . .");
					sleep(3);
					system("cls");
					break;
				}
				else{
					menu = 0;
					printf("\n\t\t  Roger that! Be careful next time. :)");
					printf("\n\n\t\t  Please wait, returning to menu . . .");
					sleep(3);
			      	system("cls");
					break;
				}
			}
		}	
	}while(menu != 4);
	
	printf("\n\n\t\t===========================================");
	printf("\n\n\t\t      Thank you for using the program!");
	printf("\n\t\t\t We hope to see you again.");
	printf("\n\n\t\t===========================================\n\n");
	
	return 0;
}

void Infix(){  //function for infix expressions
	int i, a, output, ans;
	char infix[n], element;
	
	printf("\n\t\t======================");
	printf("\n\n\t\t Kindly enter your expression (To end, please type in a tilde '~'): ");
	
	for(i = 0; i <= n - 1; i++){  //for loop to take in user input
		scanf("%c", &infix[i]);
			
		if(infix[i] == '~'){
			break;
		}
	}
	
	printf("\n\t\t     < Solution >");
	
	for(i=0; infix[i] != '~'; i++){  //for loop to scan the infix array
		element = infix[i];  //assigning the current data in the array to variable 'element'
		
		if(isdigit(element)){  //function that returns 1 if the element is a digit, otherwise returns 0
			push_num(element - '0');  //element - '0' is used for getting the digit itself rather than its ASCII code value
		}
		
		else if(element == '('){
			push_op(element);  //pushes an operator into the operators' stack
		}
		
		else if(element == ')'){
			while(op[topO] != '('){  //while loop to be executed until it encounters '(' in the operators' stack
				a = InEval(numbers, op);  //function call and assign returned value to 'a'
				push_num(a);  //returned value is pushed into the digits' stack
			}
			pop_op();  //pop the '(' from the operators' stack
		}
		
		else if(is_operator(element)){  //function call
			while(topO != -1 && priority(element) <= priority(op[topO])){  //function call
				output = InEval(numbers, op);  //function call and assign returned value to 'output'
				push_num(output);  //returned value is pushed into the digits' stack
			}
			push_op(element);  //pushes an operator into the operators' stack
		}
	}
	
	while(topO != -1){  //executed when the program finishes reading the array
		output = InEval(numbers, op);  //function call and assign returned value to 'output'
		push_num(output);  //returned value is pushed into the digits' stack
	}
	
	printf("\n\n\t\t--------------------------------------------------------");
	printf("\n\n\t\t  >> Result of expression evaluation : %d \n",pop_num());  //pops out final value computed from digits' stack
	
	emptyNumStack();  //function call
	emptyOpeStack();  //function call
	
	printf("\n\n\t\t Would you like to try again? (1 for YES, 0 for NO): ");
	scanf("%d",&ans);

	if(ans == 1){
		Infix();  //function call
	}
	else{
		printf("\n\t\t Please wait, returning to menu . . .");
		sleep(3);
      	system("cls");
      	return;
	}
}

int InEval(int numbers[50], char op[50]){  //function for evaluating infix expression
	int val, A, B;
	char ope;
	
	A = pop_num(); //pop current topmost digit in the digits' stack and assign to 'A'
	B = pop_num(); //pop current topmost digit in the digits' stack and assign to 'B'
	ope = pop_op(); //pop current topmost operator in the operators' stack and assign to 'ope'
	
	switch(ope){  //switch case to compute the expression 
		case '+':{
			val = A + B;
			printf("\n\n\t\t      %d + %d = %d", A, B, val);
			return val;
		}
		
		case '-':{
			val = B - A;
			printf("\n\n\t\t      %d - %d = %d", B, A, val);
			return val;
		}
		
		case '*':{
			val = A * B;
			printf("\n\n\t\t      %d * %d = %d", A, B, val);
			return val;
		}
		
		case '/':{
			if(A == 0){
				printf("\n\n\t\t      Cannot be divided by 0.");
				exit(0);
			}
			else{
				val = B / A;
				printf("\n\n\t\t      %d / %d = %d", A, B, val);
				return val;
			}
		}
	}
	return 0;
}

void Prefix(){  //function for prefix expressions
	int i, output, ans;
	char prefix[n], element;	
	
	printf("\n\t\t======================");
	printf("\n\n\t\t Kindly enter your expression (To end, please type in a tilde '~'): ");
	
	for(i = 0; i <= n - 1; i++){  //for loop to take in user input
        scanf("%c", &prefix[i]);
        
        if(prefix[i] == '~'){
            break;
        } 
    }
    
    printf("\n\t\t     < Solution >");
    
    for(i = strlen(prefix)-1; i>=0 ; i--){  //for loop to scan the prefix array
        element = prefix[i];  //assigning the current data in the array to variable 'element'
        
        if (isdigit(element)){  //function that returns 1 if the element is a digit, otherwise returns 0
            push_num(element - '0');  //element - '0' is used for getting the digit itself rather than its ASCII code value
        }
        
        else if(is_operator(element)){  //function call
        	push_op(element);  //pushes an operator into the operators' stack
        	output = PreEval(numbers, op);  //function call and assign returned value to 'output'
        	push_num(output);  //returned value is pushed into the digits' stack	
    	}
	}
	
    printf("\n\n\t\t--------------------------------------------------------");
    printf("\n\n\t\t  >> Result of expression evaluation : %d \n", pop_num());  //pops out final value computed from digits' stack
    
    emptyNumStack();  //function call
	emptyOpeStack();  //function call
	
	printf("\n\n\t\t Would you like to try again? (1 for YES, 0 for NO): ");
	scanf("%d",&ans);

	if(ans == 1){
		Prefix();  //function call
	}
	else{
		printf("\n\t\t Please wait, returning to menu . . .");
		sleep(3);
      	system("cls");
      	return;
	}	
}

int PreEval(int numbers[50], char op[50]){  //function for evaluating prefix expression
	int val, A, B;
	char ope;
	
	A = pop_num(); //pop current topmost digit in the digits' stack and assign to 'A'
	B = pop_num(); //pop current topmost digit in the digits' stack and assign to 'B'
	ope = pop_op();  //pop current topmost operator in the operators' stack and assign to 'ope'
	
	switch(ope){  //switch case to compute the expression
		case '*':{	
		    val = A * B;
		    printf("\n\n\t\t      %d * %d = %d", A, B, val);
		    return val;
		}
					
	    case '/':{
	        val = A / B;
		    printf("\n\n\t\t      %d / %d = %d", A, B, val);
			return val;
		}
		
		case '+':{
		    val = A + B;
		    printf("\n\n\t\t      %d + %d = %d", A, B, val);
		    return val;
		}
		
		case '-':{
		    val = A - B;
		    printf("\n\n\t\t      %d - %d = %d", A, B, val);
		    return val;
		}
	}
	return 0;
}

void Postfix(){  //function for postfix evaluation
	int i, output, ans;
	char postfix[n], element;
	
	printf("\n\t\t======================");
    printf("\n\n\t\t Kindly enter your expression (To end, please type in a tilde '~'): ");
				
	for(i = 0; i <= n - 1; i++){  //for loop to take in user input
		scanf("%c", &postfix[i]);
			
		if(postfix[i] == '~'){
			break;
		}
	}

	printf("\n\t\t     < Solution >");
	
	for(i = 0; postfix[i] != '~'; i++){  //for loop to scan the postfix array
        element = postfix[i];  //assigning the current data in the array to variable 'element'
        
        if(isdigit(element)){  //function that returns 1 if the element is a digit, otherwise returns 0
            push_num(element - '0');  //element - '0' is used for getting the digit itself rather than its ASCII code value
        }
        
        else if(is_operator(element)){  //function call
        	push_op(element);  //pushes an operator into the operators' stack
        	output = PostEval(numbers, op);  //function call and assign returned value to 'output'
        	push_num(output);  //returned value is pushed into the digits' stack
    	}
	}
    printf("\n\n\t\t--------------------------------------------------------");
    printf("\n\n\t\t  >> Result of expression evaluation : %d \n", pop_num());  //pops out final value computed from digits' stack
    
    emptyNumStack();  //function call
	emptyOpeStack();  //function call
    
	printf("\n\n\t\t Would you like to try again? (1 for YES, 0 for NO): ");
	scanf("%d",&ans);
	
	if(ans == 1){
		Postfix();  //function call
	}
	else{
		printf("\n\t\t Please wait, returning to menu . . .");
		sleep(3);
      	system("cls");
      	return;
	}				
}

int PostEval(int numbers[50], char op[50]){  //function for evaluating postfix expression
	int val, A, B;
	char ope;
	
	A = pop_num(); //pop current topmost digit in the digits' stack and assign to 'A'
	B = pop_num(); //pop current topmost digit in the digits' stack and assign to 'B'
	ope = pop_op();  //pop current topmost operator in the operators' stack and assign to 'ope'
	
	switch(ope){  //switch case to compute the expression
		case '*':{	
		    val = B * A;
		    printf("\n\n\t\t      %d * %d = %d", B, A, val);
		    return val;
		}
					
	    case '/':{
	        val = B / A;
		    printf("\n\n\t\t      %d / %d = %d", B, A, val);
			return val;
		}
		
		case '+':{
		    val = B + A;
		    printf("\n\n\t\t      %d + %d = %d", B, A, val);
		    return val;
		}
		
		case '-':{
		    val = B - A;
		    printf("\n\n\t\t      %d - %d = %d", B, A, val);
		    return val;
		}
	}
	return 0;
}

int is_operator(char ch){  //function for checking valid operators
	return(ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int priority(char ch){  //function for determining the order of priority when computing the values
	switch(ch){
		case '+':
			return 1;
		case '-':
			return 1;
		case '*':
			return 2;
		case'/':
			return 2;
	}
	return -1;
}

void push_num(int a){  //function for adding a digit in the digits' stack
	numbers[++topN] = a;
}

void push_op(char ch){  //function for adding an operator in the operators' stack
	op[++topO] = ch;
}

int pop_num(){  //function for removing a digit from the digits' stack
	return numbers[topN--];
}

char pop_op(){  //function for removing an operator from the operators' stack
	return op[topO--];
}

void emptyNumStack(){  //function for making sure that the digits' stack is empty before computing a new expression
	if(topN > -1){
		while(topN != -1){
			pop_num();
		}	
	}
	else
		return;
}

void emptyOpeStack(){  //function for making sure that the operators' stack is empty before computing a new expression
	if(topO > -1){
		while(topO != -1){
			pop_op();
		}	
	}
	else
		return;
}
