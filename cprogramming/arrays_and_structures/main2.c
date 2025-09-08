#include<stdio.h>


struct employee {
	char name[50];
	int id;
	float salary;
};

int main() {
	int ch,i;
	struct employee e[100];
	for(i=0;i<5;i++) {
		printf("enter your name :");
		//fgets(e[i].name,sizeof(e[i].name),stdin);
		//e[i].name[strcspn(e[i].name),'\n'] = '\0';
    	scanf("%[^\n]",e[i].name);
    	printf("enter your id :");
    	getchar();
		
		scanf("%d",&e[i].id);
    	printf("enter your salary :");
	    scanf("%f",&e[i].salary);
		while(ch=getchar()!='\n'&&ch!=EOF);
		printf("\n");
	}
	printf("Your details\n");
	for(i=0;i<5;i++){
		printf("Name\t:\t%s\nid\t:\t%d\nsalary\t:\t%f\n\n",e[i].name,e[i].id,e[i].salary);
	}
	return 0;
}
