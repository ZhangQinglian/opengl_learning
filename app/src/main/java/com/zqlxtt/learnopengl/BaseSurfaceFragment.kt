package com.zqlxtt.learnopengl

import android.os.Bundle
import android.view.*
import android.widget.FrameLayout
import androidx.fragment.app.Fragment

/**
 * @author 番茄沙司 created on 2020/9/24
 */
abstract class BaseSurfaceFragment : Fragment(), SurfaceHolder.Callback {

    private var surfaceView: SurfaceView? = null

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        return inflater.inflate(R.layout.fragment_base_surface, container, false);
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        surfaceView = SurfaceView(context)
        surfaceView?.let {
            val lp = FrameLayout.LayoutParams(
                FrameLayout.LayoutParams.MATCH_PARENT,
                FrameLayout.LayoutParams.MATCH_PARENT
            )
            it.layoutParams = lp
            it.holder.addCallback(this@BaseSurfaceFragment)
            getView()?.findViewById<FrameLayout>(R.id.surface_container)?.addView(it)
        }
    }

    override fun surfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {
        onSurfaceChanged(holder, format, width, height)
    }

    override fun surfaceDestroyed(holder: SurfaceHolder?) {
        onSurfaceDestroyed(holder)
    }

    override fun surfaceCreated(holder: SurfaceHolder?) {
        onSurfaceCreated(holder)
    }

    abstract fun onSurfaceCreated(holder: SurfaceHolder?)

    abstract fun onSurfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int)

    abstract fun onSurfaceDestroyed(holder: SurfaceHolder?)
}