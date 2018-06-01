using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using BansheeEngine;

namespace BansheeEditor
{
	/// <summary>Different icon sizes for project resource preview icons.</summary>
	[StructLayout(LayoutKind.Sequential), SerializeObject]
	public partial struct ProjectResourceIcons
	{
		public Texture icon16;
		public Texture icon32;
		public Texture icon48;
		public Texture icon64;
		public Texture icon96;
		public Texture icon128;
		public Texture icon192;
		public Texture icon256;
	}
}
