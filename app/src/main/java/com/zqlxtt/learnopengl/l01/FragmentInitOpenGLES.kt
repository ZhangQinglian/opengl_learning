package com.zqlxtt.learnopengl.l01

import android.util.Log
import android.view.*
import com.zqlxtt.learnopengl.BaseSurfaceFragment

class FragmentInitOpenGLES : BaseSurfaceFragment() {

    override fun onSurfaceCreated(holder: SurfaceHolder?) {
        Log.d("scott","onSurfaceCreated")
        holder?.surface?.let {
            Log.d("scott","init open gl es")
            init_opengl_es(it)
            drawColor(0.5F,0.5F,1F,1F)
        }
    }

    override fun onSurfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {
    }

    override fun onSurfaceDestroyed(holder: SurfaceHolder?) {
        Log.d("scott","onSurfaceDestroyed")
        destroy_opengl_es()
    }
}