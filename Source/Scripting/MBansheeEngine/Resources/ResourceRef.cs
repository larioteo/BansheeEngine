//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using System;
using System.Runtime.CompilerServices;

namespace BansheeEngine
{
    /** @addtogroup Resources
     *  @{
     */

    /// <summary>
    /// Provides a handle to a <see cref="Resource"/>. The underlying resource might or might not be loaded.
    /// </summary>
    public class RRefBase : ScriptObject
    {
        /// <summary>
        /// Constructor for internal use only.
        /// </summary>
        protected RRefBase() { }

        /// <summary>
        /// Checks is the referenced resource loaded.
        /// </summary>
        public bool IsLoaded => Internal_IsLoaded(mCachedPtr);

        /// <summary>
        /// Returns the referenced resource if loaded, or null otherwise.
        /// </summary>
        public Resource GenericValue => Internal_GetResource(mCachedPtr);

        /// <summary>
        /// Returns the UUID of the resource this handle is referencing.
        /// </summary>
        public UUID UUID
        {
            get
            {
                Internal_GetUUID(mCachedPtr, out var uuid);
                return uuid;
            }
        }

        /// <summary>
        /// Casts the generic resource reference type to a specific resource reference type.
        /// </summary>
        /// <typeparam name="T">Type of resource to cast the reference to.</typeparam>
        /// <returns>New reference type.</returns>
        public RRef<T> As<T>() where T : Resource
        {
            return (RRef<T>)Internal_CastAs(mCachedPtr, typeof(T));
        }

        /// <inheritdoc/>
        public override bool Equals(object other)
        {
            if (!(other is RRefBase))
                return false;

            RRefBase otherRef = (RRefBase)other;

            Internal_GetUUID(mCachedPtr, out var lhs);
            Internal_GetUUID(otherRef.mCachedPtr, out var rhs);

            return lhs.Equals(rhs);
        }

        /// <inheritdoc/>
        public override int GetHashCode()
        {
            return UUID.GetHashCode();
        }

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern bool Internal_IsLoaded(IntPtr thisPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        protected static extern Resource Internal_GetResource(IntPtr thisPtr);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern void Internal_GetUUID(IntPtr thisPtr, out UUID uuid);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern RRefBase Internal_CastAs(IntPtr thisPtr, Type type);
    }

    /// <summary>
    /// Provides a handle to a <see cref="Resource"/>. The underlying resource might or might not be loaded.
    /// </summary>
    /// <typeparam name="T">Resource type that the handle references</typeparam>
    public class RRef<T> : RRefBase where T : Resource
    {
        /// <summary>
        /// Returns the referenced resource if loaded, or null otherwise.
        /// </summary>
        public T Value => (T) GenericValue;
    }

    /** @} */
}
