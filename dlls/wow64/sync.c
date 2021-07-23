/*
 * WoW64 synchronization objects and functions
 *
 * Copyright 2021 Alexandre Julliard
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <stdarg.h>

#include "ntstatus.h"
#define WIN32_NO_STATUS
#include "windef.h"
#include "winbase.h"
#include "winnt.h"
#include "winternl.h"
#include "wow64_private.h"


/**********************************************************************
 *           wow64_NtCancelTimer
 */
NTSTATUS WINAPI wow64_NtCancelTimer( UINT *args )
{
    HANDLE handle = get_handle( &args );
    BOOLEAN *state = get_ptr( &args );

    return NtCancelTimer( handle, state );
}


/**********************************************************************
 *           wow64_NtClearEvent
 */
NTSTATUS WINAPI wow64_NtClearEvent( UINT *args )
{
    HANDLE handle = get_handle( &args );

    return NtClearEvent( handle );
}


/**********************************************************************
 *           wow64_NtCreateEvent
 */
NTSTATUS WINAPI wow64_NtCreateEvent( UINT *args )
{
    ULONG *handle_ptr = get_ptr( &args );
    ACCESS_MASK access = get_ulong( &args );
    OBJECT_ATTRIBUTES32 *attr32 = get_ptr( &args );
    EVENT_TYPE type = get_ulong( &args );
    BOOLEAN state = get_ulong( &args );

    struct object_attr64 attr;
    HANDLE handle = 0;
    NTSTATUS status;

    *handle_ptr = 0;
    status = NtCreateEvent( &handle, access, objattr_32to64( &attr, attr32 ), type, state );
    put_handle( handle_ptr, handle );
    return status;
}


/**********************************************************************
 *           wow64_NtCreateMutant
 */
NTSTATUS WINAPI wow64_NtCreateMutant( UINT *args )
{
    ULONG *handle_ptr = get_ptr( &args );
    ACCESS_MASK access = get_ulong( &args );
    OBJECT_ATTRIBUTES32 *attr32 = get_ptr( &args );
    BOOLEAN owned = get_ulong( &args );

    struct object_attr64 attr;
    HANDLE handle = 0;
    NTSTATUS status;

    *handle_ptr = 0;
    status = NtCreateMutant( &handle, access, objattr_32to64( &attr, attr32 ), owned );
    put_handle( handle_ptr, handle );
    return status;
}


/**********************************************************************
 *           wow64_NtCreateSemaphore
 */
NTSTATUS WINAPI wow64_NtCreateSemaphore( UINT *args )
{
    ULONG *handle_ptr = get_ptr( &args );
    ACCESS_MASK access = get_ulong( &args );
    OBJECT_ATTRIBUTES32 *attr32 = get_ptr( &args );
    LONG initial = get_ulong( &args );
    LONG max = get_ulong( &args );

    struct object_attr64 attr;
    HANDLE handle = 0;
    NTSTATUS status;

    *handle_ptr = 0;
    status = NtCreateSemaphore( &handle, access, objattr_32to64( &attr, attr32 ), initial, max );
    put_handle( handle_ptr, handle );
    return status;
}


/**********************************************************************
 *           wow64_NtCreateTimer
 */
NTSTATUS WINAPI wow64_NtCreateTimer( UINT *args )
{
    ULONG *handle_ptr = get_ptr( &args );
    ACCESS_MASK access = get_ulong( &args );
    OBJECT_ATTRIBUTES32 *attr32 = get_ptr( &args );
    TIMER_TYPE type = get_ulong( &args );

    struct object_attr64 attr;
    HANDLE handle = 0;
    NTSTATUS status;

    *handle_ptr = 0;
    status = NtCreateTimer( &handle, access, objattr_32to64( &attr, attr32 ), type );
    put_handle( handle_ptr, handle );
    return status;
}


/**********************************************************************
 *           wow64_NtOpenEvent
 */
NTSTATUS WINAPI wow64_NtOpenEvent( UINT *args )
{
    ULONG *handle_ptr = get_ptr( &args );
    ACCESS_MASK access = get_ulong( &args );
    OBJECT_ATTRIBUTES32 *attr32 = get_ptr( &args );

    struct object_attr64 attr;
    HANDLE handle = 0;
    NTSTATUS status;

    *handle_ptr = 0;
    status = NtOpenEvent( &handle, access, objattr_32to64( &attr, attr32 ));
    put_handle( handle_ptr, handle );
    return status;
}


/**********************************************************************
 *           wow64_NtOpenMutant
 */
NTSTATUS WINAPI wow64_NtOpenMutant( UINT *args )
{
    ULONG *handle_ptr = get_ptr( &args );
    ACCESS_MASK access = get_ulong( &args );
    OBJECT_ATTRIBUTES32 *attr32 = get_ptr( &args );

    struct object_attr64 attr;
    HANDLE handle = 0;
    NTSTATUS status;

    *handle_ptr = 0;
    status = NtOpenMutant( &handle, access, objattr_32to64( &attr, attr32 ));
    put_handle( handle_ptr, handle );
    return status;
}


/**********************************************************************
 *           wow64_NtOpenSemaphore
 */
NTSTATUS WINAPI wow64_NtOpenSemaphore( UINT *args )
{
    ULONG *handle_ptr = get_ptr( &args );
    ACCESS_MASK access = get_ulong( &args );
    OBJECT_ATTRIBUTES32 *attr32 = get_ptr( &args );

    struct object_attr64 attr;
    HANDLE handle = 0;
    NTSTATUS status;

    *handle_ptr = 0;
    status = NtOpenSemaphore( &handle, access, objattr_32to64( &attr, attr32 ));
    put_handle( handle_ptr, handle );
    return status;
}


/**********************************************************************
 *           wow64_NtOpenTimer
 */
NTSTATUS WINAPI wow64_NtOpenTimer( UINT *args )
{
    ULONG *handle_ptr = get_ptr( &args );
    ACCESS_MASK access = get_ulong( &args );
    OBJECT_ATTRIBUTES32 *attr32 = get_ptr( &args );

    struct object_attr64 attr;
    HANDLE handle = 0;
    NTSTATUS status;

    *handle_ptr = 0;
    status = NtOpenTimer( &handle, access, objattr_32to64( &attr, attr32 ));
    put_handle( handle_ptr, handle );
    return status;
}


/**********************************************************************
 *           wow64_NtPulseEvent
 */
NTSTATUS WINAPI wow64_NtPulseEvent( UINT *args )
{
    HANDLE handle = get_handle( &args );
    LONG *prev_state = get_ptr( &args );

    return NtPulseEvent( handle, prev_state );
}


/**********************************************************************
 *           wow64_NtQueryEvent
 */
NTSTATUS WINAPI wow64_NtQueryEvent( UINT *args )
{
    HANDLE handle = get_handle( &args );
    EVENT_INFORMATION_CLASS class = get_ulong( &args );
    void *info = get_ptr( &args );
    ULONG len = get_ulong( &args );
    ULONG *retlen = get_ptr( &args );

    return NtQueryEvent( handle, class, info, len, retlen );
}


/**********************************************************************
 *           wow64_NtQueryMutant
 */
NTSTATUS WINAPI wow64_NtQueryMutant( UINT *args )
{
    HANDLE handle = get_handle( &args );
    MUTANT_INFORMATION_CLASS class = get_ulong( &args );
    void *info = get_ptr( &args );
    ULONG len = get_ulong( &args );
    ULONG *retlen = get_ptr( &args );

    return NtQueryMutant( handle, class, info, len, retlen );
}


/**********************************************************************
 *           wow64_NtQuerySemaphore
 */
NTSTATUS WINAPI wow64_NtQuerySemaphore( UINT *args )
{
    HANDLE handle = get_handle( &args );
    SEMAPHORE_INFORMATION_CLASS class = get_ulong( &args );
    void *info = get_ptr( &args );
    ULONG len = get_ulong( &args );
    ULONG *retlen = get_ptr( &args );

    return NtQuerySemaphore( handle, class, info, len, retlen );
}


/**********************************************************************
 *           wow64_NtQueryTimer
 */
NTSTATUS WINAPI wow64_NtQueryTimer( UINT *args )
{
    HANDLE handle = get_handle( &args );
    TIMER_INFORMATION_CLASS class = get_ulong( &args );
    void *info = get_ptr( &args );
    ULONG len = get_ulong( &args );
    ULONG *retlen = get_ptr( &args );

    return NtQueryTimer( handle, class, info, len, retlen );
}


/**********************************************************************
 *           wow64_NtReleaseMutant
 */
NTSTATUS WINAPI wow64_NtReleaseMutant( UINT *args )
{
    HANDLE handle = get_handle( &args );
    LONG *prev_count = get_ptr( &args );

    return NtReleaseMutant( handle, prev_count );
}


/**********************************************************************
 *           wow64_NtReleaseSemaphore
 */
NTSTATUS WINAPI wow64_NtReleaseSemaphore( UINT *args )
{
    HANDLE handle = get_handle( &args );
    ULONG count = get_ulong( &args );
    ULONG *previous = get_ptr( &args );

    return NtReleaseSemaphore( handle, count, previous );
}


/**********************************************************************
 *           wow64_NtResetEvent
 */
NTSTATUS WINAPI wow64_NtResetEvent( UINT *args )
{
    HANDLE handle = get_handle( &args );
    LONG *prev_state = get_ptr( &args );

    return NtResetEvent( handle, prev_state );
}


/**********************************************************************
 *           wow64_NtSetEvent
 */
NTSTATUS WINAPI wow64_NtSetEvent( UINT *args )
{
    HANDLE handle = get_handle( &args );
    LONG *prev_state = get_ptr( &args );

    return NtSetEvent( handle, prev_state );
}


/**********************************************************************
 *           wow64_NtSetTimer
 */
NTSTATUS WINAPI wow64_NtSetTimer( UINT *args )
{
    HANDLE handle = get_handle( &args );
    LARGE_INTEGER *when = get_ptr( &args );
    ULONG apc = get_ulong( &args );
    ULONG apc_param = get_ulong( &args );
    BOOLEAN resume = get_ulong( &args );
    ULONG period = get_ulong( &args );
    BOOLEAN *state = get_ptr( &args );

    return NtSetTimer( handle, when, apc_32to64( apc ), apc_param_32to64( apc, apc_param ),
                       resume, period, state );
}
