    double* z_val = new double[1000];
    if (!z_val)
    {
        printf(">>>allocation error -> z_val\n");
        delete [] z_val;
        return -3;
    }

    for (i = 0; i < n1; i++)
    	z_val[i] = points1[i].z;
    for (i = n1; i < n1+n2; i++)
    	z_val[i] = points2[i-n1].z;
    for (i = n1 + n2; i < n1+n2+n3; i++)
    	z_val[i] = points3[i-n1-n2].z;

    for (i = 0; i < n1+n2+n3-1; i++)
    {
    	for (j = i+1; j < n1+n2+n3; j++)
    	{
    		if (z_val[i] > z_val[j])
    		{
    			val = z_val[i];
    			z_val[i] = z_val[j];
    			z_val[j] = val;
    		}
    	}
    }

    val = 0;
    for (i = 0; i < n1+n2+n3; i++) 
    { 
        if (fabs(val - z_val[i]) < 1e-14) 
        	z_val[i] = 1000; 
        else
            val = z_val[i];
    }

    for (i = 0; i < n1+n2+n3-1; i++)
    {
    	for (j = i+1; j < n1+n2+n3; j++)
    	{
    		if (z_val[i] > z_val[j])
    		{
    			val = z_val[i];
    			z_val[i] = z_val[j];
    			z_val[j] = val;
    		}
    	}
    }

    int n = 0;
    while (fabs(z_val[n] - 1000) > 1e-14)
    	n++;

    double* z_val_unique = new double[n+1];
    if (!z_val_unique)
    {
        printf(">>>allocation error -> z_val_unique\n");
        delete [] z_val_unique;
        return -3;
    }

    z_val_unique[0] = .0;
    for (i = 0; i < n; i++)
    	z_val_unique[i+1] = z_val[i];

    delete [] z_val;

    n += 1;

    for (i = 0; i < n; i++)
    	printf("%.2lf\n", z_val_unique[i]);

    delete [] z_val_unique;