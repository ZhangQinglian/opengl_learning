package com.zqlxtt.learnopengl

import android.os.Bundle
import androidx.fragment.app.Fragment
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import com.zqlxtt.learnopengl.openglstuff.OpenGLStuffs

/**
 * A fragment representing a list of Items.
 */
class OpenglStuffFragment : Fragment() {

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val view = inflater.inflate(R.layout.fragment_opengl_stuff_list, container, false)

        if (view is RecyclerView) {
            with(view) {
                layoutManager = LinearLayoutManager(context)
                adapter = MyOpenglStuffRecyclerViewAdapter(OpenGLStuffs.ITEMS)
            }
        }
        return view
    }
}