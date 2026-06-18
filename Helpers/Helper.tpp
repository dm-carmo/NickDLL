template <typename T> bool vector_contains_element(vector<T>& vec, T elem)
{
	for (DWORD i = 0; i < vec.size(); i++)
	{
		if (vec[i] == elem)
			return true;
	}
	return false;
}