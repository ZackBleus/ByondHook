#pragma once
#include <unordered_map>
#include <string>

const std::unordered_map<int, std::string> exc_code_to_msg = {
	{0x04242420, "CLRDBG_NOTIFICATION_EXCEPTION_CODE"},
	{0x40000005, "STATUS_SEGMENT_NOTIFICATION"},
	{0x40000015, "STATUS_FATAL_APP_EXIT"},
	{0x4000001C, "STATUS_WX86_UNSIMULATE"},
	{0x4000001D, "STATUS_WX86_CONTINUE"},
	{0x4000001E, "STATUS_WX86_SINGLE_STEP"},
	{0x4000001F, "STATUS_WX86_BREAKPOINT"},
	{0x40000020, "STATUS_WX86_EXCEPTION_CONTINUE"},
	{0x40000021, "STATUS_WX86_EXCEPTION_LASTCHANCE"},
	{0x40000022, "STATUS_WX86_EXCEPTION_CHAIN"},
	{0x40000028, "STATUS_WX86_CREATEWX86TIB"},
	{0x40010003, "DBG_TERMINATE_THREAD"},
	{0x40010004, "DBG_TERMINATE_PROCESS"},
	{0x40010005, "DBG_CONTROL_C"},
	{0x40010006, "DBG_PRINTEXCEPTION_C"},
	{0x40010007, "DBG_RIPEXCEPTION"},
	{0x40010008, "DBG_CONTROL_BREAK"},
	{0x40010009, "DBG_COMMAND_EXCEPTION"},
	{0x4001000A, "DBG_PRINTEXCEPTION_WIDE_C"},
	{0x406D1388, "MS_VC_EXCEPTION"},
	{0x80000001, "EXCEPTION_GUARD_PAGE"},
	{0x80000002, "EXCEPTION_DATATYPE_MISALIGNMENT"},
	{0x80000003, "EXCEPTION_BREAKPOINT"},
	{0x80000004, "EXCEPTION_SINGLE_STEP"},
	{0x80000026, "STATUS_LONGJUMP"},
	{0x80000029, "STATUS_UNWIND_CONSOLIDATE"},
	{0x80010001, "DBG_EXCEPTION_NOT_HANDLED"},
	{0xC0000005, "EXCEPTION_ACCESS_VIOLATION"},
	{0xC0000006, "EXCEPTION_IN_PAGE_ERROR"},
	{0xC0000008, "EXCEPTION_INVALID_HANDLE"},
	{0xC000000D, "STATUS_INVALID_PARAMETER"},
	{0xC0000017, "STATUS_NO_MEMORY"},
	{0xC000001D, "EXCEPTION_ILLEGAL_INSTRUCTION"},
	{0xC0000025, "EXCEPTION_NONCONTINUABLE_EXCEPTION"},
	{0xC0000026, "EXCEPTION_INVALID_DISPOSITION"},
	{0xC000008C, "EXCEPTION_ARRAY_BOUNDS_EXCEEDED"},
	{0xC000008D, "EXCEPTION_FLT_DENORMAL_OPERAND"},
	{0xC000008E, "EXCEPTION_FLT_DIVIDE_BY_ZERO"},
	{0xC000008F, "EXCEPTION_FLT_INEXACT_RESULT"},
	{0xC0000090, "EXCEPTION_FLT_INVALID_OPERATION"},
	{0xC0000091, "EXCEPTION_FLT_OVERFLOW"},
	{0xC0000092, "EXCEPTION_FLT_STACK_CHECK"},
	{0xC0000093, "EXCEPTION_FLT_UNDERFLOW"},
	{0xC0000094, "EXCEPTION_INT_DIVIDE_BY_ZERO"},
	{0xC0000095, "EXCEPTION_INT_OVERFLOW"},
	{0xC0000096, "EXCEPTION_PRIV_INSTRUCTION"},
	{0xC00000FD, "EXCEPTION_STACK_OVERFLOW"},
	{0xC0000135, "STATUS_DLL_NOT_FOUND"},
	{0xC0000138, "STATUS_ORDINAL_NOT_FOUND"},
	{0xC0000139, "STATUS_ENTRYPOINT_NOT_FOUND"},
	{0xC000013A, "STATUS_CONTROL_C_EXIT"},
	{0xC0000142, "STATUS_DLL_INIT_FAILED"},
	{0xC000014A, "STATUS_ILLEGAL_FLOAT_CONTEXT"},
	{0xC0000194, "EXCEPTION_POSSIBLE_DEADLOCK"},
	{0xC00001A5, "STATUS_INVALID_EXCEPTION_HANDLER"},
	{0xC00002B4, "STATUS_FLOAT_MULTIPLE_FAULTS"},
	{0xC00002B5, "STATUS_FLOAT_MULTIPLE_TRAPS"},
	{0xC00002C5, "STATUS_DATATYPE_MISALIGNMENT_ERROR"},
	{0xC00002C9, "STATUS_REG_NAT_CONSUMPTION"},
	{0xC0000374, "STATUS_HEAP_CORRUPTION"},
	{0xC0000409, "STATUS_STACK_BUFFER_OVERRUN"},
	{0xC0000417, "STATUS_INVALID_CRUNTIME_PARAMETER"},
	{0xC000041D, "STATUS_USER_CALLBACK"},
	{0xC0000420, "STATUS_ASSERTION_FAILURE"},
	{0xC015000F, "STATUS_SXS_EARLY_DEACTIVATION"},
	{0xC0150010, "STATUS_SXS_INVALID_DEACTIVATION"},
	{0xE0434352, "CLR_EXCEPTION"},
	{0xE06D7363, "CPP_EH_EXCEPTION"},
	{0xC06D0057, "VCPP_EXCEPTION_ERROR_INVALID_PARAMETER"},
	{0xC06D007E, "VCPP_EXCEPTION_ERROR_MOD_NOT_FOUND"},
	{0xC06D007F, "VCPP_EXCEPTION_ERROR_PROC_NOT_FOUND"},
};