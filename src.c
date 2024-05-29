#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>

#define maxuser 200
#define len 50
#define MAX_TASKS 100


typedef struct {
    int id;
    int priority;
    int duration; //seconds.
} Task;


typedef struct {
    Task tasks[MAX_TASKS];
    int count;
} TaskList;


struct User{
    char username[len];
    char password[len];
};


typedef struct User User;
User user[maxuser];
int user_id=1;
char username[len];
char password[len];

int compare_tasksP(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return (taskB->priority - taskA->priority);
}

int compare_tasksT(const void *a, const void *b) {
    Task *taskA = (Task *)a;
    Task *taskB = (Task *)b;
    return taskA->duration - taskB->duration;
}



void schedule_taskspriority(Task tasks[], int num_tasks) {
    
    qsort(tasks, num_tasks, sizeof(Task), compare_tasksP);
    
    
    printf("Scheduled Tasks:\n");
    printf("________________________________________\n");
    printf("      Task ID      |      Priority      |\n");
    printf("___________________|____________________|\n");
    for (int i = 0; i < num_tasks; i++) {
        
        
        
        printf("         %d         |         %d          |\n", tasks[i].id, tasks[i].priority);
        printf("___________________|____________________|\n");
        
    }
}

void schedule_tasks_duration(Task tasks[], int num_tasks) {
    // Sort tasks based on duration
    qsort(tasks, num_tasks, sizeof(Task), compare_tasksT);
    
    // Print the scheduled tasks
    printf("Scheduled Tasks:\n");
    printf("________________________________________\n");
    printf("      Task ID      |   Time Duration    |\n");
    printf("___________________|____________________|\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("         %d         |         %d          |\n", tasks[i].id, tasks[i].duration);
        printf("___________________|____________________|\n");
    }
}


void robinround(Task tasks[], int num_tasks) {
    // Sort tasks based on duration
    
    // Print the scheduled tasks
    printf("Scheduled Tasks:\n");
    printf("________________________________________\n");
    printf("      Task ID      |        ORDER       |\n");
    printf("___________________|____________________|\n");
    for (int i = 0; i < num_tasks; i++) {
        printf("         %d         |         %d          |\n", tasks[i].id, i+1);
        printf("___________________|____________________|\n");
    }
}

void addTask(TaskList *taskList, int id, int priority, int duration) {
    if (taskList->count < MAX_TASKS) {
        Task newTask = {id, priority, duration};
        taskList->tasks[taskList->count++] = newTask;
        printf("Task %d added\n", id);
    } else {
        printf("Task list full, cannot add more tasks\n");
    }
}


void scheduleTaskscompleteP(TaskList *taskList) {
    printf("Scheduling tasks...\n");

    
    qsort(taskList->tasks, taskList->count, sizeof(Task), compare_tasksP);
    
    for (int i = 0; i < taskList->count; ++i) {
        Task task = taskList->tasks[i];
        printf("Executing Task %d with priority %d and duration %d seconds\n",
               task.id, task.priority, task.duration);
        sleep(task.duration);
        printf("Task %d completed\n", task.id);
    }
    printf("All tasks completed.\n");
}

void scheduleTaskscompleteT(TaskList *taskList) {
    printf("Scheduling tasks...\n");

    
    qsort(taskList->tasks, taskList->count, sizeof(Task), compare_tasksT);
    
    for (int i = 0; i < taskList->count; ++i) {
        Task task = taskList->tasks[i];
        printf("Executing Task %d with priority %d and duration %d seconds\n",
               task.id, task.priority, task.duration);
        sleep(task.duration);
        printf("Task %d completed\n", task.id);
    }
    printf("All tasks completed.\n");
}


void robinroundcomplete(TaskList *taskList) {
    printf("Scheduling tasks...\n");
    for (int i = 0; i < taskList->count; ++i) {
        Task task = taskList->tasks[i];
        printf("Executing Task %d with priority %d and duration %d seconds\n",
               task.id, task.priority, task.duration);
        sleep(task.duration);
        printf("Task %d completed\n", task.id);
    }
    printf("All tasks completed.\n");
}

void adduser(){
    int error=0;
    printf("------------------Add User-------------------\n");
    printf("Enter username : ");
    scanf("%s",username);
    for (int i=0;i<user_id;i++){
        if (strcmp(user[i].username,username)==0){
            printf("Username already exist...\n");
            error=1;
        }
    }
    if(error==1){
        adduser();
    }else{
        printf("Enter password : ");
        scanf("%s",password);
    
        if(user_id<maxuser){
            strcpy(user[user_id].username,username);
            strcpy(user[user_id].password,password);
            user_id++;
            printf("Adding user %s...\n",username);
            sleep(2);
            printf("User - %s added successfully.\n ",username);
        }else printf("Cannot add user. maximum user limit reached.\n");
    }
}


void loginuser(){
    printf("-----------------User login------------------\n");
    printf("Username : ");
    scanf("%s",username);
    printf("Password : ");
    scanf("%s",password);
    int check=0,num_tasks;
    for (int i=0;i<user_id;i++){
        if (strcmp(user[i].username,username)==0 && strcmp(user[i].password,password)==0)
            check=1;
        
    }
    
    if(check==1) printf("Login successfull.\n");
    else    printf("Login failed! .Invalid username and password or add user first.\n");
    if(check==1){
        int opt;
            while(opt!=4){
            printf("\n");
            printf("1. Add Task.\n2. Scheduling.\n3. Completing task.\n4. Exit\n");
            printf("Enter your choice : ");
            scanf("%d",&opt);
            switch(opt){
                case 1:
                printf("\nEnter the number of tasks: ");
                scanf("%d", &num_tasks);
                Task *tasks = (Task *)malloc(num_tasks * sizeof(Task));
                
                for (int i = 0; i < num_tasks; i++) {
                    printf("Enter task details (ID , Priority, Duration):\n");
                    scanf("%d %d %d", &tasks[i].id, &tasks[i].priority, &tasks[i].duration);
                }
                    TaskList taskList = {{}, 0};
                    for(int i=0;i<num_tasks;i++){
                
                        addTask(&taskList, tasks[i].id, tasks[i].priority, tasks[i].duration);
                    }
                break;
                
                case 2:// Schedule tasks.
                printf("\n");
                printf("1. Order based.\n2. Time based.\n3. Priority based.\n4. Exit\n");
                printf("Enter your choice : ");
                scanf("%d",&opt);
                if(opt==3)
                
                schedule_taskspriority(tasks, num_tasks);
                else if(opt==2)
                schedule_tasks_duration(tasks, num_tasks);
                else if(opt==1)
                robinround(tasks, num_tasks);
                else printf("Invalid option.\n");
                break;
                
                case 3:// complete task.
                printf("\n");
                printf("1. Order based.\n2. Time based.\n3. Priority based.\n4. Exit\n");
                printf("Enter your choice : ");
                scanf("%d",&opt);
                if(opt==1)
                scheduleTaskscompleteP(&taskList);
                else if(opt==2)
                scheduleTaskscompleteT(&taskList);
                else if(opt==3)
                robinroundcomplete(&taskList);
                else printf("Invalid option.\n");
                
                break;
                
                case 4:
                printf("Exiting...\n");
                break;
                
                default:
                    printf("Invalid option!\n");
                    break;
                }
            }
            
        }
        
}




int main(){
    int op,check=0;
    while(op!=3){
        printf("\n");
        printf("1. User login.\n2. Add user.\n3. Exit.\n");
        printf("Enter option : ");
        scanf("%d",&op);
        switch(op){
            case 1:
            loginuser();
            break;
            case 2:
            adduser();
            break;
            case 3:
            printf("Exiting...\n");
            break;
            default:
            printf("Invalid!\n");
            break;
        }
    }
    
    return 0;
}
