package com.zqlxtt.learnopengl.L1

import android.view.*
import com.zqlxtt.learnopengl.BaseSurfaceFragment

class FragmentInitOpenGLES : BaseSurfaceFragment() {

    override fun onSurfaceCreated(holder: SurfaceHolder?) {
        holder?.surface?.let {
            init_opengl_es(it)
        }
    }

    override fun onSurfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {
    }

    override fun onSurfaceDestroyed(holder: SurfaceHolder?) {
        destroy_opengl_es()
    }


    external fun init_opengl_es(surface: Surface)
    external fun destroy_opengl_es();
}