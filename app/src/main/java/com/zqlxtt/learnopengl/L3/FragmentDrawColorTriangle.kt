package com.zqlxtt.learnopengl.L3

import android.util.Log
import android.view.SurfaceHolder
import com.zqlxtt.learnopengl.BaseSurfaceFragment

class FragmentDrawColorTriangle : BaseSurfaceFragment() {
    override fun onSurfaceCreated(holder: SurfaceHolder?) {
        holder?.surface?.let {
            Log.d("scott", "init open gl es")
            init_opengl_es(it)
            drawColorTriangle()
        }
    }

    override fun onSurfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {
    }

    override fun onSurfaceDestroyed(holder: SurfaceHolder?) {
        destroy_opengl_es()
    }

}