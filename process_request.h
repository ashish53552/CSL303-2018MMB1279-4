struct total* calc_time(struct request *req){
	float rps=r/(float)60;
	float rotational_time=1000/rps;
	float time_per_each_sector=rotational_time/sectors;
	float rotational_latency=rotational_time/2;
	float data_rate=heads*sectors*sector_size*rps;
	struct total *temp=(struct total * ) malloc(sizeof(struct total));
	float start_cylinder=start->cylinder;
	float start_sector=start->sector;
	float req_cylinder=req->l->cylinder;
	float req_sector=req->l->sector;
	int diff_cy=req_cylinder-start_cylinder;
	if(diff_cy<0) diff_cy=-1*diff_cy;
	int diff_sector;
	if(req_sector>=start_sector) diff_sector=req_sector-start_sector;
	else diff_sector=req_sector+ sectors-start_sector;
	start->platter=req->l->platter;
	start->cylinder=req_cylinder;
	start->sector=((int)(req_sector+req->requestedSectors))%sectors;
	temp->seek_time=diff_cy*tc + diff_sector*time_per_each_sector;
	temp->read_write_time= temp->seek_time + req->requestedSectors*time_per_each_sector;
	return temp;

}
