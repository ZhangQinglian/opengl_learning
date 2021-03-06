package com.zqlxtt.learnopengl.l04

import android.view.Surface
import android.view.SurfaceHolder
import com.zqlxtt.learnopengl.BaseSurfaceFragment

class FragmentEGLThread : BaseSurfaceFragment() {
    override fun onSurfaceCreated(holder: SurfaceHolder?) {
        holder?.surface?.let {
            drawTriangleWithThread(it)
            onSurfaceCreatedN(it);
        }
    }

    override fun onSurfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {
        onSurfaceChangedN(width,height)
    }

    override fun onSurfaceDestroyed(holder: SurfaceHolder?) {
        onSurfaceDestroyN()
    }

    external fun drawTriangleWithThread(surface:Surface);
}