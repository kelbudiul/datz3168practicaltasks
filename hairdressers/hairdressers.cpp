

main()
{
	using namespace std;

	ifstream ifile;
	ofstream ofile;

	int hairdressers, a, b, c, time, d, e;

	Queue q(9);
	MinHeap h(100000);

	ifile.open("hair.in");
	ofile.open("hair.out", ofstream::out | ofstream::trunc);
	ifile >> hairdressers;
	for (int i = 0; i <= hairdressers; i++)
	{
		q.enqueu(i);
	}

	ifile >> a;
	time = a;

	while (a > 0)
	{
		ifile >> b >> c;
		if (!q.empty())
		{
			if (time < a)
			{
				time = a;
			}
			d = (time / 100) % 10;
			e = ((time + c - 1) / 100) % 10;

			if (d >= q.peek() && e <= q.peek())
			{
				time = time / 100 + q.peek() * 100 + (10 - q.peek()) * 100 + 100;
				h.insertKey(time + c - 1, q.peek(), b);
			}
			else if (d <= q.peek() && e >= q.peek())
			{
				time = time / 100 + (q.peek() - d) * 100 + 100;
				h.insertKey(time + c - 1, q.peek(), b);
			}
			else
			{
				h.insertKey(time + c - 1, q.peek(), b);
			}

			q.dequeue(); // First in the queue now was removed from the list of barber who are free
		}
		else // Случай когда все парихмахеры заняты
		{
			h.extractMin();
			ofile << h.resource_arr[0] << " " << h.resource_arr[1] << " " << h.resource_arr[2] << endl;

			if (time < h.resource_arr[0] + 1)
			{
				time = h.resource_arr[0] + 1;
			}

			if (time < a)
			{
				time = a;
			}

			d = (time / 100) % 10;
			e = ((time + c - 1) / 100) % 10;

			if (d >= h.resource_arr[1] && e <= h.resource_arr[1])
			{
				time = time / 100 + h.resource_arr[1] * 100 + (10 - h.resource_arr[1]) * 100 + 100;
				h.insertKey(time + c - 1, h.resource_arr[1], b);
			}
			else if (d <= h.resource_arr[1] && e >= h.resource_arr[1])
			{
				time = time / 100 + (h.resource_arr[1] - d) * 100 + 100;
				h.insertKey(time + c - 1, h.resource_arr[1], b);
			}
			else
			{
				h.insertKey(time + c - 1, h.resource_arr[1], b);
			}
		}
		ifile >> a;
	}
	ifile.close();

	while (h.hsize > 0)
	{
		h.extractMin();
		ofile << h.resource_arr[0] << " " << h.resource_arr[1] << " " << h.resource_arr[2] << endl;
	}

	ofile.close();
	return 0;
}
