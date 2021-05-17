// for (i = 0; i < count; i++)
	// {
	// 	cur = z_min + 1e-3;
	// 	j = 2;
	// 	n_new = n[i];
	// 	while (cur < z_max)
	// 	{
	// 		if (fabs(cur - points[i][j].z) > 1e-3)
	// 		{
	// 			points[i][n_new].z = cur;
	// 			points[i][n_new].x = (points[i][j-1].x + points[i][j].x)/2.0;
	// 			points[i][n_new].y = (points[i][j-1].y + points[i][j].y)/2.0;
	// 			n_new++;
	// 		}
	// 		cur += 1e-3;
	// 	}
	// 	n[i] = n_new;
	// }

	// for (i = 0; i < count; i++)
	// {
	// 	for (j = 0; j < n[i]-1; j++)
	// 	{
	// 		for (k = j+1; k < n[i]; k++)
	// 		{
	// 			if (points[i][j].z > points[i][k].z)
	// 			{
	// 				val = points[i][j].x;
	// 				points[i][j].x = points[i][k].x;
	// 				points[i][k].x = val;

	// 				val = points[i][j].y;
	// 				points[i][j].y = points[i][k].y;
	// 				points[i][k].y = val;

	// 				val = points[i][j].z;
	// 				points[i][j].z = points[i][k].z;
	// 				points[i][k].z = val;
	// 			}
	// 		}
	// 	}
	// }

	// k = 0;
	// for (i = 0; i < n[k]; i++)
	// 	printf("%lf\n", points[k][i].z);

	// for (i = 0; i < count; i++)
	// {
	// 	for (j = 0; j < n[i]; j++)
	// 	{
	// 		if (fabs(points[i][j].z) < 1e-14)
	// 		{
	// 			n[i] = j;
	// 			break;
	// 		}
	// 	}
	// }