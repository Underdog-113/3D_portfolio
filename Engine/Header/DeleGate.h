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
		std::function::target 템플릿 멤버 함수를 사용 할 때, 템플릿 클래스의 템플릿 멤버 함수를 호출하게
		되면 컴파일러가 타입을 제대로 추론하지 못해 템플릿 멤버 함수에 대해서 컴파일 오류를 발생 시킨다. 때문에 컴파일러에게
		명시적으로 템플릿 함수라는 것을 알려 주기 위해 함수의 호출 부 앞에 'template' 키워드를 붙여 주었다.
		*/

		const std::size_t func_hash = func.target_type().hash_code();
		/*
		삭제 하려는 함수의 해쉬 코드 값과 함수 포인터를 얻어온다.
		여기서 주목 해야 할 부분은, 클래스 멤버 함수나, 람다의 경우는 <void(*)(ARGS...)> 타입이 아니기 때문에 target을 이용해 함수 포인터를 얻어 오려고 하면
		nullptr을 리턴한다. 반대로 일반 함수의 경우는 target_type을 이용해 해쉬 코드를 얻어 오면 같은 포멧의 함수는 같은 해쉬 코드를 리턴하기 때문에 구분이 불가능 하다.
		그래서 위 코드의 29 ~ 52 라인 처럼 일반 함수와 다른 타입의 함수들을 구분 해서 처리 해줘야 한다.
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