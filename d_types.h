struct result{
	float throughput;
	float avg;
	float min;
	float max;
	float std_dev;
};
struct location{
	int platter,cylinder,sector;
};
struct request{
	struct location *l;
	int requestedSectors;
};
struct total{
	float seek_time;
	float read_write_time;
};


int limits=1000;
int surf=4,heads=4,cylinders=25,sectors=20;
float r,ts,sector_size,tc;
struct location *start;