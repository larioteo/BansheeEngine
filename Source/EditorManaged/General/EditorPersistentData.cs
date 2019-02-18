//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
using bs;
using System.Collections.Generic;

namespace bs.Editor
{
    /** @addtogroup General
     *  @{
     */

    /// <summary>
    /// Contains editor data that should persist assembly refresh.
    /// </summary>
    internal class EditorPersistentData : ManagedComponent
    {
        [SerializeField]
        internal Dictionary<UUID, bool> dirtyResources = new Dictionary<UUID, bool>();

        [SerializeField]
        internal Dictionary<UUID, EditorAnimClipInfo> dirtyAnimClips = new Dictionary<UUID, EditorAnimClipInfo>();
    }

    /** @} */
}
