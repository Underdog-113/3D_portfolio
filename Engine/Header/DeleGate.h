// Delegate.h
#ifndef _DELEGATE_H_
#define _DELEGATE_H_

#include <list>
#include <functional>

BEGIN(Engine)
template <class... ARGS>
class ENGINE_DLL Delegate
{
public:
	typedef typename std::list<std::function<void(ARGS...)>>::iterator iterator;

	void operator () (const ARGS... args)
	{
		for (auto& func : functions)
		{
			func(args...);
		}
	}

	Delegate& operator += (std::function<void(ARGS...)> const& func)
	{
		functions.push_back(func);
		return *this;
	}
	
	Delegate& operator -= (std::function<void(ARGS...)> const& func)
	{
		void(*const* func_ptr)(ARGS...) = func.template target<void(*)(ARGS...)>();
		/*
		std::function::target ���ø� ��� �Լ��� ��� �� ��, ���ø� Ŭ������ ���ø� ��� �Լ��� ȣ���ϰ�
		�Ǹ� �����Ϸ��� Ÿ���� ����� �߷����� ���� ���ø� ��� �Լ��� ���ؼ� ������ ������ �߻� ��Ų��. ������ �����Ϸ�����
		��������� ���ø� �Լ���� ���� �˷� �ֱ� ���� �Լ��� ȣ�� �� �տ� 'template' Ű���带 �ٿ� �־���.
		*/

		const std::size_t func_hash = func.target_type().hash_code();
		/*
		���� �Ϸ��� �Լ��� �ؽ� �ڵ� ���� �Լ� �����͸� ���´�.
		���⼭ �ָ� �ؾ� �� �κ���, Ŭ���� ��� �Լ���, ������ ���� <void(*)(ARGS...)> Ÿ���� �ƴϱ� ������ target�� �̿��� �Լ� �����͸� ��� ������ �ϸ�
		nullptr�� �����Ѵ�. �ݴ�� �Ϲ� �Լ��� ���� target_type�� �̿��� �ؽ� �ڵ带 ��� ���� ���� ������ �Լ��� ���� �ؽ� �ڵ带 �����ϱ� ������ ������ �Ұ��� �ϴ�.
		�׷��� �� �ڵ��� 29 ~ 52 ���� ó�� �Ϲ� �Լ��� �ٸ� Ÿ���� �Լ����� ���� �ؼ� ó�� ����� �Ѵ�.
		*/

		if (nullptr == func_ptr)
		{
			for (auto itr = functions.begin(); itr != functions.end(); itr++)
			{
				if (func_hash == (*itr).target_type().hash_code())
				{
					functions.erase(itr);
					return *this;
				}
			}
		}
		else
		{
			for (auto itr = functions.begin(); itr != functions.end(); itr++)
			{
				void(*const* delegate_ptr)(ARGS...) = (*itr).template target<void(*)(ARGS...)>();
				if (nullptr != delegate_ptr && *func_ptr == *delegate_ptr)
				{
					functions.erase(itr);
					return *this;
				}
			}
		}
		return *this;
	}

	iterator begin() noexcept
	{
		return functions.begin();
	}
	iterator end() noexcept
	{
		return functions.end();
	}
	void clear()
	{
		functions.clear();
	}

private:
	std::list<std::function<void(ARGS...)>> functions;
};
END
#endif