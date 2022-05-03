

#include	<stdio.h>
#include	<stdlib.h>

#include	"dcll.h"

list_t list1 = NULL;
list_t list2 = NULL;

struct node2* r_data = 0;

struct node2
{
	int data;
};

void showdata(data_t data)
{
	fprintf(stdout, "{%d}->", ((struct node2*)data)->data);
}

void deletedata(data_t data)
{
	fprintf(stdout, "deleting: %d\n", ((struct node2*)data)->data);
	free(data);
}

bool_t compare_proc(data_t data1, data_t data2)
{
	if( ((struct node2*)data1)->data == ((struct node2*)data2)->data )
		return(SUCCESS);

	return(FAILURE);
}

bool_t compare_proc2(data_t data1, data_t data2)
{
	if( ((struct node2*)data1)->data < ((struct node2*)data2)->data )
		return(SUCCESS);

	return(FAILURE);
}

int main(void)
{
	list1 = list_create();
	list2 = list_create();

	fprintf(stdout, "List Insert First:\n");
	for(int i = 0; i < 10; ++i)
	{
		struct node2* pdata = (struct node2*) malloc(sizeof(struct node2));
		pdata->data = (i + 1) * 10;
		list_insert_front(list1, pdata);
	}
	list_show(list1, showdata);

	fprintf(stdout, "List Insert Back:\n");
	for(int i = 10; i < 20; ++i)
	{
		struct node2* pdata = (struct node2*) malloc(sizeof(struct node2));
		pdata->data = (i + 1) * 10;
		list_insert_back(list1, pdata);
	}
	list_show(list1, showdata);

	fprintf(stdout, "List Insert Position:\n");
	
	struct node2* pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 55;
	list_insert_position(list1, pdata, 1);
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 45;
	list_insert_position(list1, pdata, 3);
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 35;
	list_insert_position(list1, pdata, 5);
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 15;
	list_insert_position(list1, pdata, 8);
	list_show(list1, showdata);

	fprintf(stdout, "List Insert After:\n");
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 100;
	struct node2* pdata2 = (struct node2*) malloc(sizeof(struct node2));
	pdata2->data = 105;
	list_insert_after(list1, pdata, pdata2, compare_proc);
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 20;
	pdata2 = (struct node2*) malloc(sizeof(struct node2));
	pdata2->data = 25;
	list_insert_after(list1, pdata, pdata2, compare_proc);
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 70;
	pdata2 = (struct node2*) malloc(sizeof(struct node2));
	pdata2->data = 75;
	list_insert_after(list1, pdata, pdata2, compare_proc);
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 60;
	pdata2 = (struct node2*) malloc(sizeof(struct node2));
	pdata2->data = 65;
	list_insert_after(list1, pdata, pdata2, compare_proc);
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 120;
	pdata2 = (struct node2*) malloc(sizeof(struct node2));
	pdata2->data = 125;
	list_insert_after(list1, pdata, pdata2, compare_proc);
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 170;
	pdata2 = (struct node2*) malloc(sizeof(struct node2));
	pdata2->data = 175;
	list_insert_after(list1, pdata, pdata2, compare_proc);
	
	list_show(list1, showdata);

	fprintf(stdout, "List Insert Before:\n");
	
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 60;
	pdata2 = (struct node2*) malloc(sizeof(struct node2));
	pdata2->data = 55;
	list_insert_after(list1, pdata, pdata2, compare_proc);

	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 90;
	pdata2 = (struct node2*) malloc(sizeof(struct node2));
	pdata2->data = 85;
	list_insert_after(list1, pdata, pdata2, compare_proc);
	
	
	pdata = (struct node2*) malloc(sizeof(struct node2));
	pdata->data = 100;
	pdata2 = (struct node2*) malloc(sizeof(struct node2));
	pdata2->data = 95;
	list_insert_after(list1, pdata, pdata2, compare_proc);
	list_show(list1, showdata);

	fprintf(stdout, "List Remove Front:\n");

	list_remove_front(list1, &r_data);
	fprintf(stdout, "%d is removed\n", ((struct node2*)r_data)->data);
	
	list_remove_front(list1, &r_data);
	fprintf(stdout, "%d is removed\n", ((struct node2*)r_data)->data);
	
	list_remove_front(list1, &r_data);
	fprintf(stdout, "%d is removed\n", ((struct node2*)r_data)->data);
	
	list_remove_front(list1, NULL);
	list_remove_front(list1, NULL);
	list_remove_front(list1, NULL);
	
	list_show(list1, showdata);

	fprintf(stdout, "List Remove Back:\n");
	list_remove_back(list1, &r_data);
	fprintf(stdout, "%d is removed\n", ((struct node2*)r_data)->data);
	list_remove_back(list1, &r_data);
	fprintf(stdout, "%d is removed\n", ((struct node2*)r_data)->data);
	list_remove_back(list1, &r_data);
	fprintf(stdout, "%d is removed\n", ((struct node2*)r_data)->data);
	list_remove_back(list1, NULL);
	list_remove_back(list1, NULL);
	list_remove_back(list1, NULL);
	list_show(list1, showdata);

	fprintf(stdout, "List Remove:\n");
	pdata2 = (struct node2*) malloc(sizeof(struct node2));
	pdata2->data = 10;
	list_remove(list1, pdata2, &r_data, compare_proc);
	fprintf(stdout, "%d is removed\n", ((struct node2*)r_data)->data);
	pdata2->data = 20;
	list_remove(list1, pdata2, &r_data, compare_proc);
	fprintf(stdout, "%d is removed\n", ((struct node2*)r_data)->data);
	r_data = 0;
	pdata2->data = 30;
	list_remove(list1, pdata2, &r_data, compare_proc);
	fprintf(stdout, "%d is removed\n", ((struct node2*)r_data)->data);
	list_show(list1, showdata);

	fprintf(stdout, "List 2:\n");
	for(int i = 0; i < 10; ++i)
	{
		struct node2* pdata = (struct node2*) malloc(sizeof(struct node2));
		pdata->data = (i + 1) * 13;
		list_insert_front(list2, pdata);
	}
	list_show(list2, showdata);
	list_show(list1, showdata);

	fprintf(stdout, "List Merge:\n");
	list_t mlist = list_merge(list1, list2, compare_proc2);
	list_show(mlist, showdata);

	fprintf(stdout, "List Concate:\n");
	list_t clist = list_concate(list1, list2);
	list_show(clist, showdata);

	fprintf(stdout, "List Reverse:\n");
	list_reverse(clist);
	list_show(clist, showdata);

	fprintf(stdout, "List Append:\n");
	list_show(list1, showdata);
	list_show(list2, showdata);
	list_append(list1, list2);
	list_show(list1, showdata);
	list_show(list2, showdata);
	list_show(mlist, showdata);

	fprintf(stdout, "List Destroy:L1\n");
	list_destroy((pp_list_t)&list1, deletedata);
	fprintf(stdout, "List Destroy:L2\n");
	list_destroy((pp_list_t)&list2, deletedata);
	
	fprintf(stdout, "List Destroy:L3\n");
	list_show(mlist, showdata);
	list_destroy((pp_list_t)&mlist, deletedata);
	
	fprintf(stdout, "List Destroy:L4\n");
	//list_destroy((pp_list_t)&clist, deletedata);

	fprintf(stdout, "List Show:\n");
	list_show(list1, showdata);
	list_show(list2, showdata);
	list_show(mlist, showdata);
	list_show(clist, showdata);

	return(SUCCESS);
}

