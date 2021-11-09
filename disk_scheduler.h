
struct request * FIFO(struct request * request_arr,int limits){

	return request_arr;
}


//Random, FIFO, SSTF, SCAN, C-SCAN

struct request * Random(struct request * request_arr,int limits){
	struct request * queue_arr=(struct request *) malloc(limits *sizeof(struct request));
	int finish=0;
	int done[limits];
	srand(time(NULL));
	for(int i=0;i<limits;i++) done[i]=0;
	while(finish<limits){
		int el=rand()%limits;
		if(!done[el]){
			queue_arr[finish]=request_arr[el];
			finish++;
			done[el]=1;
		}
	}

	return queue_arr;
}

struct request * SCAN(struct request * request_arr,int limits){
	struct request * queue_arr=(struct request *) malloc(limits *sizeof(struct request));
	struct location temp_start;
	int done[limits];
	int finish=0;
	for(int i=0;i<limits;i++) done[i]=0;
	for(int i=start->cylinder;i<cylinders;i++){
		for(int j=0;j<limits;++j){
			if(!done[j] &&  request_arr[j].l->cylinder==i){
				queue_arr[finish++]=request_arr[j];
				done[j]=1;
			}
		}
		if(finish==limits-1) break;
	}
	for(int i=start->cylinder-1;i>=0;i--){
		for(int j=0;j<limits;++j){
			if(!done[j] &&  request_arr[j].l->cylinder==i){
				queue_arr[finish++]=request_arr[j];
				done[j]=1;
			}
		}
		if(finish==limits-1) break;
	}
	return queue_arr;
}

struct request * SSTF(struct request * request_arr,int limits){
	struct request * queue_arr=(struct request *) malloc(limits *sizeof(struct request));
	struct location temp_start;
	int done[limits];
	for(int i=0;i<limits;i++) done[i]=0;
	float time_arr[limits];
	
	temp_start=*start;
	for(int j=0;j<limits;j++){
		float min_time=1e6;
		int min_index=0;
		for(int i=0;i<limits;i++){
			if(!done[i]){
				*start=temp_start;
				struct total *t=calc_time(&request_arr[i]);
				time_arr[i]=t->read_write_time;
				if(time_arr[i]<min_time){
					min_index=i;
					min_time=time_arr[i];
				}
			}else{
				time_arr[i]=1e6;
			}
			
		}
		calc_time(&request_arr[min_index]);
		temp_start=*start;
		queue_arr[j]=request_arr[min_index];
		done[min_index]=1;
	}
	
	
	
	return queue_arr;
}

struct request * C_SCAN(struct request * request_arr,int limits){
	struct request * queue_arr=(struct request *) malloc(limits *sizeof(struct request));
	struct location temp_start;
	int done[limits];
	int finish=0;
	for(int i=0;i<limits;i++) done[i]=0;
	for(int i=start->cylinder;i<cylinders;i++){
		for(int j=0;j<limits;++j){
			if(!done[j] &&  request_arr[j].l->cylinder==i){
				queue_arr[finish++]=request_arr[j];
				done[j]=1;
			}
		}
		if(finish==limits-1) break;
	}
	for(int i=0;i<start->cylinder;i++){
		for(int j=0;j<limits;++j){
			if(!done[j] &&  request_arr[j].l->cylinder==i){
				queue_arr[finish++]=request_arr[j];
				done[j]=1;
			}
		}
		if(finish==limits-1) break;
	}
	return queue_arr;
}
	