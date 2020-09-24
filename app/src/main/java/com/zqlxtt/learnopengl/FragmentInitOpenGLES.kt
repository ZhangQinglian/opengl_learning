package com.zqlxtt.learnopengl

import android.os.Bundle
import android.view.*
import androidx.fragment.app.Fragment
import kotlinx.android.synthetic.main.fragment_init_open_g_l_e_s.*

class FragmentInitOpenGLES : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        return inflater.inflate(R.layout.fragment_init_open_g_l_e_s, container, false)
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        surface.holder.addCallback(object : SurfaceHolder.Callback {
            override fun surfaceChanged(
                holder: SurfaceHolder?,
                format: Int,
                width: Int,
                height: Int
            ) {

            }

            override fun surfaceDestroyed(holder: SurfaceHolder?) {
                destroy_opengl_es()
            }

            override fun surfaceCreated(holder: SurfaceHolder?) {
                holder?.surface?.let {
                    init_opengl_es(it)
                }
            }

        })
    }


    external fun init_opengl_es(surface: Surface)
    external fun destroy_opengl_es();
}