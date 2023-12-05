#include <stdio.h>
#include <string.h>

#define MAX_TASKS 100

typedef struct {
    char title[100];
    char date[20];
    int duration;
    int completed;
    int priority; // 0: Low, 1: Medium, 2: High
} Task;

void displayTasks(Task tasks[], int count, const char* currentDate) {
    printf("Tasks for %s:\n", currentDate);
    for (int i = 0; i < count; ++i) {
        printf("%d. %s (Due: %s, Duration: %d, Priority: %d, Completed: %s)\n",
            i + 1, tasks[i].title, tasks[i].date, tasks[i].duration,
            tasks[i].priority, tasks[i].completed ? "Yes" : "No");
    }
}

void markTaskAsCompleted(Task* task) {
    task->completed = 1;
}

void setTaskPriority(Task* task, int priority) {
    task->priority = priority;
}

void editTaskDate(Task* task, const char* newDate) {
    strcpy(task->date, newDate);
}

void addTask(Task tasks[], int* count) {
    printf("Enter task title: ");
    scanf("%s", tasks[*count].title);

    printf("Enter due date (YYYY-MM-DD): ");
    scanf("%s", tasks[*count].date);

    printf("Enter task duration (in minutes): ");
    scanf("%d", &tasks[*count].duration);

    tasks[*count].completed = 0; // Set new task as not completed by default

    printf("Enter task priority (0: Low, 1: Medium, 2: High): ");
    scanf("%d", &tasks[*count].priority);

    (*count)++;
}

void saveTasksToFile(Task tasks[], int count, const char* filePath) {
    FILE* file = fopen(filePath, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < count; ++i) {
        fprintf(file, "%s,%s,%d,%d,%d\n", tasks[i].title, tasks[i].date, tasks[i].duration, tasks[i].completed, tasks[i].priority);
    }

    fclose(file);
}

void loadTasksFromFile(Task tasks[], int* count, const char* filePath) {
    FILE* file = fopen(filePath, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return;
    }

    *count = 0;
    while (fscanf(file, "%99[^,],%19[^,],%d,%d,%d\n", tasks[*count].title, tasks[*count].date, &tasks[*count].duration, &tasks[*count].completed, &tasks[*count].priority) == 5) {
        (*count)++;
    }

    fclose(file);
}

int main() {
    Task tasks[MAX_TASKS];
    int taskCount = 0;

    // Load tasks from file (if any)
    loadTasksFromFile(tasks, &taskCount, "Ukolovnik.txt");

    char currentDate[20];

    while (1) {
        printf("\nOptions:\n");
        printf("1. Display tasks for the current date\n");
        printf("2. Mark a task as completed\n");
        printf("3. Set task priority\n");
        printf("4. Edit task date\n");
        printf("5. Add a new task\n");
        printf("6. Save tasks to file and exit\n");
        printf("Choose an option (1-6): ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter current date (YYYY-MM-DD): ");
            scanf("%s", currentDate);
            displayTasks(tasks, taskCount, currentDate);
            break;
        case 2:
            printf("Enter task number to mark as completed: ");
            int taskNumber;
            scanf("%d", &taskNumber);
            if (taskNumber > 0 && taskNumber <= taskCount) {
                markTaskAsCompleted(&tasks[taskNumber - 1]);
                printf("Task marked as completed.\n");
            }
            else {
                printf("Invalid task number.\n");
            }
            break;
        case 3:
            printf("Enter task number to set priority: ");
            int priorityTaskNumber, priority;
            scanf("%d", &priorityTaskNumber);
            if (priorityTaskNumber > 0 && priorityTaskNumber <= taskCount) {
                printf("Enter priority (0: Low, 1: Medium, 2: High): ");
                scanf("%d", &priority);
                setTaskPriority(&tasks[priorityTaskNumber - 1], priority);
                printf("Priority set.\n");
            }
            else {
                printf("Invalid task number.\n");
            }
            break;
        case 4:
            printf("Enter task number to edit date: ");
            int editDateTaskNumber;
            scanf("%d", &editDateTaskNumber);
            if (editDateTaskNumber > 0 && editDateTaskNumber <= taskCount) {
                printf("Enter new date (YYYY-MM-DD): ");
                scanf("%s", currentDate);
                editTaskDate(&tasks[editDateTaskNumber - 1], currentDate);
                printf("Date edited.\n");
            }
            else {
                printf("Invalid task number.\n");
            }
            break;
        case 5:
            if (taskCount < MAX_TASKS) {
                addTask(tasks, &taskCount);
                printf("Task added.\n");
            }
            else {
                printf("Maximum number of tasks reached.\n");
            }
            break;
        case 6:
            // Save tasks to file before exiting
            saveTasksToFile(tasks, taskCount, "Ukolovnik.txt");
            printf("Tasks saved to file. Exiting...\n");
            return 0;
        default:
            printf("Invalid option. Please choose a valid option (1-6).\n");
        }
    }

    return 0;
}
