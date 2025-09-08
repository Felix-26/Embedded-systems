#include<stdio.h>

struct Employee {
	char name[32];
	int id;
	float salary;
};

int main() {
	struct Employee e = {"Felix Thomas",101,300000};
	struct Employee p = {"Ann Maria Thomas",102,250000};
	struct Employee w = {"Margeret C Joseph",103,275000};
	printf("Name\t:\t%s\nid\t:\t%d\nsalary\t:\t%.2f\n\n",e.name,e.id,e.salary);
	printf("Name\t:\t%s\nid\t:\t%d\nsalary\t:\t%.2f\n\n",p.name,p.id,p.salary);
	printf("Name\t:\t%s\nid\t:\t%d\nsalary\t:\t%.2f\n\n",w.name,w.id,w.salary);
	return 0;
}
