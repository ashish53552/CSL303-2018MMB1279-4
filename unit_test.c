#include"headers.h"




void take_input(){
	start= (struct location *) malloc(sizeof(struct location));
	start->platter=0;
	start->cylinder=0;
	start->sector=0;
	printf("Enter Rotational speed of disk, r revolutions per minute\n");
    scanf("%f",&r);
    printf("Enter Average seek time, Ts in ms\n");
	scanf("%f",&ts);
	printf("Enter Sector size, N in bytes\n");
	scanf("%f",&sector_size);
	tc=(2*ts)/(cylinders-1);
	return;
}

struct result* throughput_fun(struct request * queue_arr){
	struct result  *temp= (struct result *) malloc(sizeof(struct result));
	float time_arr[limits];
	
	for(int i=0;i<limits;i++){
		struct total *t=calc_time(&queue_arr[i]);
		time_arr[i]=t->read_write_time;
	}
	
	
	float sum=0;
	float min=1e6;
	float max=-1;
	for(int i=0;i<limits;i++){
		sum+=time_arr[i];
		if(min>time_arr[i]) min=time_arr[i];
		if(max<time_arr[i]) max=time_arr[i];
	}
	temp->min=min;
	temp->avg=sum/limits;
	temp->max=max;
	temp->throughput=limits*1000/sum;
	sum=0;
	for(int i=0;i<limits;i++){
		sum+=pow((temp->avg-time_arr[i]),2);
	}
	sum/=limits;
	temp->std_dev=sqrt(sum);
	return temp;
}
struct request * generate(){
	struct request * request_arr=(struct request *) malloc(limits*sizeof(struct request ));
	srand(time(NULL));
	for(int i=0;i<limits;i++){
		struct request temp;
		temp.l= (struct location *) malloc(sizeof(struct location));
		temp.l->cylinder=rand()%cylinders;
		temp.l->platter=rand()%heads;
		temp.l->sector=rand()%sectors;
		temp.requestedSectors=rand()%sectors +1;
		request_arr[i]=temp;

	}
	return request_arr;
}

int main(){


	take_input();
	struct request * request_arr=generate();
    printf("Generated Request array:\n");
    for(int i=0;i<limits;i++){
        printf("[Platter %d, cylinder %d, sector %d, requested sectors %d]\n",request_arr[i].l->platter,request_arr[i].l->cylinder,request_arr[i].l->sector,request_arr[i].requestedSectors);
    }
	struct request* queue_arr;
	struct result *res;
	printf("-------------------------FIFO--------------------------\n");
    printf("FIFO queue array:\n");
	queue_arr=FIFO(request_arr,limits);
    for(int i=0;i<limits;i++){
        printf("[Platter %d, cylinder %d, sector %d, requested sectors %d]\n",queue_arr[i].l->platter,queue_arr[i].l->cylinder,queue_arr[i].l->sector,queue_arr[i].requestedSectors);
    }
	res=throughput_fun(queue_arr);
	printf("Throughput (requests/s)= %f\n",res->throughput);
	printf("<Avg.= %f, Min.= %f, Max.= %f, StdDev.= %f> of response time (ms)\n",res->avg,res->min,res->max,res->std_dev);


	printf("\n\n-------------------------Random--------------------------\n");
    printf("Random queue array:\n");
	queue_arr=Random(request_arr,limits);
    for(int i=0;i<limits;i++){
        printf("[Platter %d, cylinder %d, sector %d, requested sectors %d]\n",queue_arr[i].l->platter,queue_arr[i].l->cylinder,queue_arr[i].l->sector,queue_arr[i].requestedSectors);
    }
	res=throughput_fun(queue_arr);
	printf("Throughput (requests/s)= %f\n",res->throughput);
	printf("<Avg.= %f, Min.= %f, Max.= %f, StdDev.= %f> of response time (ms)\n",res->avg,res->min,res->max,res->std_dev);

	
	printf("\n\n-------------------------SSTF--------------------------\n");
    printf("SSTF queue array:\n");
	queue_arr=SSTF(request_arr,limits);
    for(int i=0;i<limits;i++){
        printf("[Platter %d, cylinder %d, sector %d, requested sectors %d]\n",queue_arr[i].l->platter,queue_arr[i].l->cylinder,queue_arr[i].l->sector,queue_arr[i].requestedSectors);
    }
	res=throughput_fun(queue_arr);
	printf("Throughput (requests/s)= %f\n",res->throughput);
	printf("<Avg.= %f, Min.= %f, Max.= %f, StdDev.= %f> of response time (ms)\n",res->avg,res->min,res->max,res->std_dev);

		
	printf("\n\n-------------------------SCAN--------------------------\n");
    printf("SCAN queue array:\n");
	queue_arr=SCAN(request_arr,limits);
    for(int i=0;i<limits;i++){
        printf("[Platter %d, cylinder %d, sector %d, requested sectors %d]\n",queue_arr[i].l->platter,queue_arr[i].l->cylinder,queue_arr[i].l->sector,queue_arr[i].requestedSectors);
    }
	res=throughput_fun(queue_arr);
	printf("Throughput (requests/s)= %f\n",res->throughput);
	printf("<Avg.= %f, Min.= %f, Max.= %f, StdDev.= %f> of response time (ms)\n",res->avg,res->min,res->max,res->std_dev);

	printf("\n\n-------------------------C-SCAN--------------------------\n");
    printf("C-SCAN queue array:\n");
	queue_arr=C_SCAN(request_arr,limits);
    for(int i=0;i<limits;i++){
        printf("[Platter %d, cylinder %d, sector %d, requested sectors %d]\n",queue_arr[i].l->platter,queue_arr[i].l->cylinder,queue_arr[i].l->sector,queue_arr[i].requestedSectors);
    }
	res=throughput_fun(queue_arr);
	printf("Throughput (requests/s)= %f\n",res->throughput);
	printf("<Avg.= %f, Min.= %f, Max.= %f, StdDev.= %f> of response time (ms)\n",res->avg,res->min,res->max,res->std_dev);



	return 0;
}