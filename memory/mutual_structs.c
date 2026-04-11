#include <stdio.h>
#include <stdlib.h>


typedef struct Employee employee_t;
typedef struct Department department_t;

struct Employee {
    int id;
    char *name;
    department_t *department;
};

struct Department {
    char *name;
    employee_t *manager;
};

employee_t create_employee(int id, char *name);
department_t create_department(char *name);
void assign_employee(employee_t *emp, department_t *department);
void assign_manager(department_t *dept, employee_t *manager);

employee_t create_employee(int id, char *name) {
    employee_t emp = {
        .id = id,
        .name = name,
        .department = NULL,
    };
    return emp;
}

department_t create_department(char *name) {
    department_t dept = {
        .name = name,
        .manager = NULL,
    };
    return dept;
}

void assign_employee(employee_t *emp, department_t *department) {
    emp->department = department;
}

void assign_manager(department_t *dept, employee_t *manager) {
    dept->manager = manager;
}

int main(void) {
    employee_t emp = create_employee(1, "Ava");
    department_t dept = create_department("Engineering");

    assign_employee(&emp, &dept);
    assign_manager(&dept, &emp);

    printf("%s works in %s\n", emp.name, emp.department->name);
    printf("%s manages %s\n", dept.manager->name, dept.name);

    return 0;
}