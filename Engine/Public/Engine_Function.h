#ifndef Engine_Function_h__
#define Engine_Function_h__

namespace Engine
{
	// 템플릿은 기능의 정해져있으나 자료형은 정해져있지 않은 것
	// 기능을 인스턴스화 하기 위하여 만들어두는 틀

	template<typename T>
	void	Safe_Delete(T& pPointer)
	{
		if (nullptr != pPointer)
		{
			delete pPointer;
			pPointer = nullptr;
		}
	}

	template<typename T>
	void	Safe_Delete_Array(T& pPointer)
	{
		if (nullptr != pPointer)
		{
			delete [] pPointer;
			pPointer = nullptr;
		}
	}

	template<typename T>
	unsigned int Safe_Release(T& pInstance)
	{
		unsigned int		iRefCnt = 0;

		if (nullptr != pInstance)
		{
			iRefCnt = pInstance->Release();

			if (0 == iRefCnt)
				pInstance = nullptr;
		}
		return iRefCnt;
	}

	template<typename T>
	unsigned int Safe_AddRef(T& pInstance)
	{
		unsigned int		iRefCnt = 0;

		if (nullptr != pInstance)		
			iRefCnt = pInstance->AddRef();

		return iRefCnt;
	}

	template<typename T>
	void writeVectorToBinary(std::vector<T>& vec, std::ostream& os) {
		// 벡터의 요소 개수를 이진 파일에 쓰기
		size_t size = vec.size();
		os.write((char*)(&size), sizeof(size_t));
		// 벡터의 각 요소를 이진 파일에 쓰기
		os.write((char*)(vec.data()), sizeof(T) * size);
	}

	template<typename T>
	void readVectorFromBinary(std::istream& is, std::vector<T>& vec) {
		// 벡터의 요소 개수를 이진 파일에서 읽어오기
		size_t size;
		is.read((char*)(&size), sizeof(size_t));
		// 벡터의 크기를 조정하여 메모리를 할당
		vec.resize(size);
		// 벡터의 요소를 이진 파일에서 읽어오기
		is.read((char*)(vec.data()), sizeof(T) * size);
	}



}

#endif // Engine_Function_h__
