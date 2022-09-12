//
// file:			wlac4_internal_header_base.h
// path:			include/wlac4/wlac4_internal_header_base.h
// created on:		2022 Sep 12
// created by:		Davit Kalantaryan (davit.kalantaryan@gmail.com)
//

#ifndef WLAC4_INCLUDE_WLAC4_WLAC4_INTERNAL_HEADER_BASE_H
#define WLAC4_INCLUDE_WLAC4_WLAC4_INTERNAL_HEADER_BASE_H

#include <stddef.h>

#define wlac4_alloca	alloca

#ifdef _MSC_VER

	#if defined(_WIN64) || defined(_M_ARM)
		#define WLAC4_FNAME_PREFIX ""
		#define WLAC4_DS_FNAME_POSTFIX
		#define WLAC4_SEC_CH_FNC_NAME	"__security_check_cookie"
	#else
		#define WLAC4_FNAME_PREFIX "_"
		#define WLAC4_DS_FNAME_POSTFIX	"@12"
		#define WLAC4_SEC_CH_FNC_NAME	"@__security_check_cookie@4"
	#endif

    #define WLAC4_C_CODE_INITIALIZER_RAW(_sect,f) \
        __pragma(section(_sect,read)) \
        static void f(void); \
        __declspec(allocate(_sect)) void (*f##_)(void) = f; \
        __pragma(comment(linker,"/include:" WLAC4_FNAME_PREFIX #f "_")) \
        static void f(void)

    #define WLAC4_C_CODE_INITIALIZER(f)  WLAC4_C_CODE_INITIALIZER_RAW(".CRT$XCU",f)

	#undef wlac4_alloca
	#define wlac4_alloca	_alloca
	#define WLAC4_UNREACHABLE_CODE(_code)
	//#if _MSC_FULL_VER
	#if (_MSC_VER>1900) // 1900 is VS2015
		#pragma warning (disable:5045)
	#endif
	// assignment within conditional expression (https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4706?view=msvc-160)
	#pragma warning (disable:4706) 
	// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4711?view=msvc-160
	#pragma warning (disable:4711)
	// Function not inlined althou defined to be inline. 
	// this can happen also with library functions, so this should be disabled
	// https://docs.microsoft.com/en-us/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4711?view=msvc-160
	#pragma warning (disable:4710)
	#define WLAC4_BEFORE_CPP_17_FALL_THR
    #define WLAC4_DLL_PUBLIC		__declspec(dllexport)
    #define WLAC4_DLL_PRIVATE
    #define WLAC4_IMPORT_FROM_DLL	__declspec(dllimport)
	#define WLAC4_THREAD_LOCAL		__declspec(thread)
	#if !defined(_WIN64) && !defined(_M_ARM64)
		#define CPPUTLS_32_BIT
	#endif
#elif defined(__GNUC__) || defined(__clang__) || defined(LINUX_GCC)
    #define WLAC4_MAY_ALIAS  __attribute__ ((__may_alias__))
	#define WLAC4_UNREACHABLE_CODE(_code)	_code ;
	#if __GNUC__>=7
		#define WLAC4_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
	#elif defined(__has_attribute)
		#if __has_attribute (fallthrough)
			#define WLAC4_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
		#else
			#define WLAC4_BEFORE_CPP_17_FALL_THR		/* FALLTHRU */
		#endif
	#else
		#define WLAC4_BEFORE_CPP_17_FALL_THR		/* FALLTHRU */
	#endif  // #if __GNUC__>=7
    //#define WLAC4_DLL_PUBLIC		__attribute__((visibility("default")))
    #define WLAC4_DLL_PUBLIC
    #define WLAC4_DLL_PRIVATE		__attribute__((visibility("hidden")))
    #define WLAC4_IMPORT_FROM_DLL
	#define WLAC4_THREAD_LOCAL		__thread
#elif defined(__CYGWIN__)
	#define WLAC4_UNREACHABLE_CODE(_code)	_code ;
	#define WLAC4_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
    #define WLAC4_DLL_PUBLIC		__attribute__((dllexport))
    #define WLAC4_DLL_PRIVATE
    #define WLAC4_IMPORT_FROM_DLL	__attribute__((dllimport))
#elif defined(__MINGW64__) || defined(__MINGW32__)
	#define WLAC4_UNREACHABLE_CODE(_code)	_code ;
	#define WLAC4_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ;
    #define WLAC4_DLL_PUBLIC		_declspec(dllexport)
    #define WLAC4_DLL_PRIVATE
    #define WLAC4_IMPORT_FROM_DLL	_declspec(dllimport)
#elif defined(__SUNPRO_CC)
	#define WLAC4_UNREACHABLE_CODE(_code)	_code ;
	// #define WLAC4_BEFORE_CPP_17_FALL_THR	__attribute__ ((fallthrough)) ; // ???
	#define WLAC4_BEFORE_CPP_17_FALL_THR
    #define WLAC4_DLL_PUBLIC
    #define WLAC4_DLL_PRIVATE		__hidden
    #define WLAC4_IMPORT_FROM_DLL
#endif  // #ifdef _MSC_VER

#if defined(_MSC_VER) && defined(_MSVC_LANG)
	#if (_MSVC_LANG>=201100L)
		#define WLAC4_CPP_11_DEFINED		1
	#endif
	#if (_MSVC_LANG>=201400L)
		#define WLAC4_CPP_14_DEFINED		1
	#endif
	#if (_MSVC_LANG>=201700L)
		#define WLAC4_CPP_17_DEFINED		1
	#endif
	#if (_MSVC_LANG>=202000L)
		#define WLAC4_CPP_20_DEFINED		1
	#endif
	#if (_MSVC_LANG>=202300L)
		#define WLAC4_CPP_23_DEFINED		1
	#endif
#elif defined(__cplusplus)  // #if defined(_MSC_VER) && defined(_MSVC_LANG)
	#if (__cplusplus>=201100L)
		#define WLAC4_CPP_11_DEFINED		1
	#endif
	#if (__cplusplus>=201400L)
		#define WLAC4_CPP_14_DEFINED		1
	#endif
	#if (__cplusplus>=201700L)
		#define WLAC4_CPP_17_DEFINED		1
	#endif
	#if (__cplusplus>=202000L)
		#define WLAC4_CPP_20_DEFINED		1
	#endif
	#if (__cplusplus>=202300L)
		#define WLAC4_CPP_23_DEFINED		1
	#endif
#endif // #if defined(_MSC_VER) && defined(_MSVC_LANG)


//#undef WLAC4_CPP_11_DEFINED


//#define WLAC4_RESTRICT   restrict
#define WLAC4_RESTRICT

#ifndef WLAC4_MAY_ALIAS
#define WLAC4_MAY_ALIAS
#endif

#ifdef __cplusplus
#define WLAC4_STATIC_CAST(_type,_data)		static_cast<_type>(_data)
#define WLAC4_REINTERPRET_CAST(_type,_data)	reinterpret_cast<_type>(_data)
#define WLAC4_CONST_CAST(_type,_data)		const_cast<_type>(_data)
#define WLAC4_DYNAMIC_CAST(_type,_data)		dynamic_cast<_type>(_data)
#define WLAC4_GLOBAL	   ::
#define WLAC4_BEGIN_C   extern "C" {
#define WLAC4_END_C     }
#define WLAC4_EXTERN_C  extern "C"
#else
#define WLAC4_STATIC_CAST(_type,_data)		((_type)(_data))
#define WLAC4_REINTERPRET_CAST(_type,_data)	((_type)(_data))
#define WLAC4_CONST_CAST(_type,_data)		((_type)(_data))
#define WLAC4_DYNAMIC_CAST(_type,_data)		((_type)(_data))
#define WLAC4_GLOBAL
#define WLAC4_BEGIN_C
#define WLAC4_END_C
#define WLAC4_EXTERN_C
#endif


#ifdef WLAC4_CPP_17_DEFINED
#define WLAC4_FALLTHROUGH	[[fallthrough]] ;
#else
#define WLAC4_FALLTHROUGH	WLAC4_BEFORE_CPP_17_FALL_THR 
//#define WLAC4_FALLTHROUGH	
#endif

//#undef WLAC4_CPP_11_DEFINED
//#undef WLAC4_CPP_14_DEFINED

#ifdef WLAC4_CPP_11_DEFINED
#define WLAC4_STD_MOVE_DEFINED   1
#define WLAC4_NOEXCEPT           noexcept
#define WLAC4_NULL               nullptr
#define WLAC4_OVERRIDE           override
//#define WLAC4_CONSTEXPR          constexpr
//#define WLAC4_CONSTEXPR_CONS     constexpr
#define WLAC4_CONSTEXPR          constexpr
#define WLAC4_CONSTEXPR_FNC          constexpr
#define WLAC4_CONSTEXPR_EQ(_exp)	= (_exp)
#define WLAC4_DELETE             =delete;
#define WLAC4_CONSTEXPR_STACK_ARRAY(_type,_name,_count)	_type _name[_count]
#else
#define WLAC4_NOEXCEPT	throw()
#define WLAC4_NULL		NULL 
#define WLAC4_OVERRIDE
#define WLAC4_CONSTEXPR	const
#define WLAC4_CONSTEXPR_FNC
#define WLAC4_CONSTEXPR_EQ(_exp)
#define WLAC4_DELETE   {}
#define WLAC4_CONSTEXPR_STACK_ARRAY(_type,_name,_count)	_type * _name = WLAC4_STATIC_CAST(  _type *,wlac4_alloca((_count)*sizeof(_type))  )
#endif

#ifdef WLAC4_CPP_14_DEFINED
#define WLAC4_CONSTEXPR_FNC_CPP14     constexpr
#else
#define WLAC4_CONSTEXPR_FNC_CPP14
#endif

#ifdef __cplusplus
#define WLAC4_REGISTER
#else
#define WLAC4_REGISTER	register
#endif


//#define WLAC4_IS_LITTLE_ENDIAN (((union { unsigned x; unsigned char c; }){1}).c)

#if defined(_DEBUG) || defined(WLAC4_DEBUG)
// we have debug compilation
#else
// we have release
#ifndef NDEBUG
// let's define NDEBUG (No DEBUG)
#define NDEBUG
#endif
#endif

#ifdef NDEBUG
#define WLAC4_DO_DEBUG_EXP(_exp)
#define WLAC4_SAFE_CAST(_type,_val)	static_cast<_type>(_val)
#else
#define WLAC4_DO_DEBUG_EXP(_exp)              _exp ;
#define WLAC4_SAFE_CAST(_type,_val)	dynamic_cast<_type>(_val)
#endif


#define WLAC4_NO_NULL

#define WLAC4_STRINGIFY(_x)                WLAC4_STRINGIFY_PRIV_RAW(_x)
#define WLAC4_STRINGIFY_PRIV_RAW(_x)		#_x


#if defined(__EMSCRIPTEN__) || defined(EMSCRIPTEN) || defined(WLAC4_WASM)
#define WLAC4_EMSCRIPTEN_IS_USED
#endif
//#define WLAC4_EMSCRIPTEN_IS_USED

#ifdef WLAC4_EMSCRIPTEN_IS_USED
#ifdef WLAC4_DLL_PUBLIC
#undef WLAC4_DLL_PUBLIC
#endif
#include <emscripten/emscripten.h>
#define WLAC4_DLL_PUBLIC     EMSCRIPTEN_KEEPALIVE
#endif

// todo: make better multithreading decision
#if !defined(WLAC4_EMSCRIPTEN_IS_USED) && !defined(WLAC4_FORCE_SINGLE_THREADED)
#define WLAC4_MULTITHREADED
#endif

// todo: make better possible no file dfecision
#ifdef WLAC4_EMSCRIPTEN_IS_USED
#define WLAC4_POSSIBLE_NO_PERS_FILE
#endif

#ifdef WLAC4_MULTITHREADED
#define WLAC4_TRY_CATCH(_expression,_result)	(_expression) ;
#else
#define WLAC4_TRY_CATCH(_expression,_result)   try{(_expression);}catch(...){return _result;}
#endif

#define WLAC4_IN_OUT

// https://gcc.gnu.org/bugzilla/show_bug.cgi?id=56480
#ifdef __GNUC__
#define WLAC4_GCC_BUG_56480
#endif

#ifdef WLAC4_CPP_20_DEFINED
#define WLAC4_NODISCARD	[[nodiscard]]
#elif defined(WLAC4_CPP_11_DEFINED)
#define WLAC4_NODISCARD	noexcept
#else
#define WLAC4_NODISCARD	throw()
#endif


#endif  // #ifndef WLAC4_INCLUDE_WLAC4_WLAC4_INTERNAL_HEADER_BASE_H
