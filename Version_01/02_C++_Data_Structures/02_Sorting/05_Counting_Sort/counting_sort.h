

#pragma	once

template<typename T>
void 	Counting_Sort(	std::vector<T>& arr,
						size_t range)
{
	std::vector<size_t> count(range+1);
	size_t index;

	std::vector<T> temp(arr);

	for( int i = 0; i < temp.size(); ++i )
	{
		++count[ **temp[i] ];
	}

	for( size_t i = 1; i < count.size(); ++i )
	{
		count[i] += count[i-1];
	}

	for (int i = 0; i < temp.size(); ++i)
	{
		arr[ count[ **temp[i] ] - 1] = temp[i];
		--count[ **temp[i] ];
	}
}
