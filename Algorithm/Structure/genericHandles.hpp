
#pragma once
#ifndef __GENERIC_HANDLE__H
#define __GENERIC_HANDLE__H

template <class T>
void g_delete(T data)
    {
    
    }
    
template <class T>
bool genericEquality(const T& left, const T& right)
	{
	return left == right;
	}
	
#endif /* __GENERIC_HANDLE__H */