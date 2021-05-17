std::vector <double>* z_values[count];

	z_values[0] = new vector <double> (18000);

	for (i = 1; i < count; i++)
	{
		z_values[i] = new vector <double> (200);
		if (!z_values[i])
        {
            printf(">>>allocation error\n");
            for (j = 0; j < count; j++)
            	delete [] z_values[j];
            return -1;
        }
	}

	for (i = 0; i < 18000; i++)
		z_values[0]->at(j) = .0;

	for (i = 1; i < count; i++)
	{
		for (j = 0; j < 200; j++)
			z_values[i]->at(j) = .0;
	}

	// printf("%lf\n", z_values[99]->at(0));

	for (i = 0; i < count; i++)
	{
		for (j = 0; j < n_plus[i]; j++)
			z_values[i]->at(j) = points[i][j].z;
	}

	// k = 99;
	// for (j = 0; j < n_plus[k]; j++)
	// 	printf("%lf\n", z_values[k]->at(j));

	int n_z_plus = n_plus[0];

	for (i = 1; i < count; i++)
	{
		for (j = 1; j < n_plus[i]-1; j++)
		{
			flag = 0;
			for (k = 1; k < n_z_plus; k++)
			{
				if (fabs(z_values[i]->at(j) - z_values[0]->at(k)) < 1e-3)
					flag = 1;
			}
			if (flag == 0)
			{
				z_values[0]->push_back (z_values[i]->at(j));
				n_z_plus++;
			}
			// printf("\tchecked elems = %d\n", j);
		}
	}

	printf("n_plus[0] = %d\n", n_plus[0]);
	printf("n_z_plus = %d\n", n_z_plus);

	for (i = 0; i < n_z_plus; i++)
		printf("%lf\n", z_values[0]->at(i));