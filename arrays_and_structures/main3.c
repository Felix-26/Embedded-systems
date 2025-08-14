#include<stdio.h>

struct Employee {
        char name[32];
        int id;
        float salary;
};

void increment(struct Employee e,float percent) {
	e.salary += e.salary*percent/100;
	printf("%f",e.salary);
}

int main() {
        struct Employee e = {"Felix Thomas",101,300000};
        struct Employee p = {"Ann Maria Thomas",102,250000};
        struct Employee w = {"Margeret C Joseph",103,275000};
		increment(e,10.0);
		printf("\n%f\n",e.salary);
        printf("\nName\t:\t%s\nid\t:\t%d\nsalary\t:\t%.2f\n\n",e.name,e.id,e.salary);
        return 0;
}
