#include<stdio.h>
#include<stdlib.h>
typedef struct state_node
{
int s;
struct state_node *next;
}state_node;
typedef struct alpha_node{
char alpha;
struct alpha_node * next;
} alpha_node;

static int num_states,num_alpha,num_transitions,s1,s2;
char alphabets[20],c;
alpha_node *transition_table[20][20]={NULL};
struct state_node * state_ptr[20] = {NULL};
struct state_node * nfa_trans_table[20][20] = {NULL}; // state * alphabets 2D array
/* util function to print the transition_table*/
void print_trantable(){
int i,j;
alpha_node *iter;
for(i=1; i<= num_states;i++){
for(j=1; j <= num_states;j++){
iter = transition_table[i][j];
printf("%d to %d : ",i,j);
while(iter != NULL){
printf("%c ->", iter->alpha);

iter = iter -> next;
}
printf("\n");
}
printf("\n");
}
}
void print_nfa_trantable(){
int i,j;
state_node *iter;
for(i=1; i<= num_states;i++){
for(j=0; j < num_alpha;j++){
iter = nfa_trans_table[i][j];
printf("state : %d input: %c : ",i,alphabets[j]);
while(iter != NULL){
printf("%d ->", iter->s);
iter = iter -> next;
}
printf("\n");
}
printf("\n");
}
}
void add_nfa_trans(int s1, char alpha, int s2){
int i;
state_node *node_ptr = (state_node *)malloc(sizeof(state_node));
for(i=0; i<num_alpha; i++){
if(alpha == alphabets[i]){
node_ptr->s = s2;
break;
}
}
if(nfa_trans_table[s1][i] == NULL){
nfa_trans_table[s1][i] = node_ptr;
}

else{
state_node *temp = nfa_trans_table[s1][i];
while(temp->next != NULL){
temp = temp->next;
}
temp->next = node_ptr;
}
}

void add_transition(int s1, char alpha, int s2){
alpha_node *ptr = (alpha_node *)malloc(sizeof(alpha_node));
ptr->alpha = alpha;
ptr->next = NULL;
add_nfa_trans(s1,alpha,s2);
if(transition_table[s1][s2] == NULL){
transition_table[s1][s2] = ptr;
}
else{
alpha_node *temp = transition_table[s1][s2];
while(temp->next != NULL){
temp = temp->next;
}
temp->next = ptr;
}
}
struct state_node* find_closure(int state){
int j;
struct state_node *ptr = (struct state_node *)malloc(sizeof(struct state_node));
struct state_node *head;
struct state_node * prev;
head = ptr;
ptr->s = state;
prev = ptr;

state_ptr[state] = ptr;
for(j=1; j<=num_states; j++){
alpha_node *node_ptr = transition_table[state][j];
while(node_ptr != NULL){
if(node_ptr->alpha == 'e'){
ptr = find_closure(j);
prev -> next = ptr;
prev = ptr;
while(prev->next != NULL)
prev = prev -> next;
break;
}
else{
node_ptr = node_ptr -> next;
}
}
}
return head;
}
void print_e_closure(){
int i;
struct state_node * ptr = (struct state_node *)malloc(sizeof(struct state_node));
for(i = 1; i<= num_states; i++){
ptr = state_ptr[i];
printf("e-closure of %d : ", i);
while(ptr != NULL){
printf("%d ",ptr->s);
ptr = ptr->next;
}
printf("\n");
}
}
state_node * find_next_states_on_input_of(int state, int alpha_index){
return nfa_trans_table[state][alpha_index];// can be NULL

}

void update_nfa_trantable(int state, int alpha_index){ //need to refactor this :/
state_node *first_e_closure = state_ptr[state];
state_node *next_states,*head,*prev, *node, *second_e_closure;
head = NULL;
int first_state,s, second_state;
int has_included_state[20] = {0}; //flag array
while(first_e_closure != NULL){ // first_e_closure has all the states reachable
from s on ip alpha
s = first_e_closure->s; //find the e-closure of all such states by taking one at
a time
next_states = find_next_states_on_input_of(s, alpha_index);
while(next_states != NULL){ //for each state, add the e-closure of the state to the
table entry (state, alpha)
first_state = next_states->s;
second_e_closure = state_ptr[first_state];
while(second_e_closure != NULL){
second_state = second_e_closure -> s;
if(!has_included_state[second_state]){ //check if the state has been

already included

node = (state_node *) malloc(sizeof(state_node));
node ->s = second_state;
if(head == NULL){
head = node;
}
else{
prev -> next = node;
}
prev = node;
has_included_state[second_state] = 1;
}
second_e_closure = second_e_closure -> next;
}
next_states = next_states ->next;

}
first_e_closure = first_e_closure->next;
}
nfa_trans_table[state][alpha_index] = head;
}
int main()
{
int i, alpha_index,state;
struct state_node *temp;

printf("Enter the number of alphabets (excluding e): ");
scanf("%d", &num_alpha);
printf("Enter the alphabets (as a single string, no spaces): ");
scanf("%s", alphabets);
printf("\nEnter the number of states? : ");
scanf("%d",&num_states);
printf("\nEnter no of transition? : ");
scanf("%d",&num_transitions);

printf("\nEnter transition? (eg 1 a 2) : ");
for(i=0;i<num_transitions;i++)
{
scanf("%d %c %d",&s1,&c,&s2);
add_transition(s1,c,s2);
}
printf("\n");
for(state = 1; state<= num_states; state++){
find_closure(state);
}
for(state=1;state<=num_states;state++){
for(alpha_index=0;alpha_index<num_alpha;alpha_index++){

update_nfa_trantable(state,alpha_index);
}
}
//print_trantable();
printf("\n");
print_nfa_trantable();
//print_e_closure();
}
