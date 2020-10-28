package com.zqlxtt.learnopengl.l05

import android.view.Surface
import android.view.SurfaceHolder
import com.zqlxtt.learnopengl.BaseSurfaceFragment

class RenderTriangleFragment : BaseSurfaceFragment() {
    override fun onSurfaceCreated(holder: SurfaceHolder?) {
        holder?.let {
            initDrawTriangleWithRender(it.surface);
        }
    }

    override fun onSurfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {
        onSurfaceChanged05(width, height);
    }

    override fun onSurfaceDestroyed(holder: SurfaceHolder?) {
        onSurfaceDestroyed05();
    }

    private external fun initDrawTriangleWithRender(surface: Surface)
    private external fun onSurfaceChanged05(width: Int, height: Int);
    private external fun onSurfaceDestroyed05();
}