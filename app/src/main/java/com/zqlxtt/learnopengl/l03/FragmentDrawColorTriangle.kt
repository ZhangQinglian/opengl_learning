package com.zqlxtt.learnopengl.l03

import android.util.Log
import android.view.SurfaceHolder
import com.zqlxtt.learnopengl.BaseSurfaceFragment

class FragmentDrawColorTriangle : BaseSurfaceFragment() {
    override fun onSurfaceCreated(holder: SurfaceHolder?) {
        holder?.surface?.let {
            Log.d("scott", "init open gl es")
            drawColorTriangle(it)
        }
    }

    override fun onSurfaceChanged(holder: SurfaceHolder?, format: Int, width: Int, height: Int) {
    }

    override fun onSurfaceDestroyed(holder: SurfaceHolder?) {
    }

}