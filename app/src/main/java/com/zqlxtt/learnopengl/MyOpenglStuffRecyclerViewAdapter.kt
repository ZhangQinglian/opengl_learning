package com.zqlxtt.learnopengl

import androidx.recyclerview.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.navigation.findNavController

import com.zqlxtt.learnopengl.openglstuff.OpenGLStuffs.OpenGLESLearningItem

/**
 * [RecyclerView.Adapter] that can display a [OpenGLESLearningItem].
 * TODO: Replace the implementation with code for your data type.
 */
class MyOpenglStuffRecyclerViewAdapter(
    private val values: List<OpenGLESLearningItem>
) : RecyclerView.Adapter<MyOpenglStuffRecyclerViewAdapter.ViewHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(parent.context)
            .inflate(R.layout.fragment_opengl_stuff_item, parent, false)
        return ViewHolder(view)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        holder.bind(values[position])
    }

    override fun getItemCount(): Int = values.size

    inner class ViewHolder(view: View) : RecyclerView.ViewHolder(view) {
        val wrapperView = view.findViewById<View>(R.id.item_wrapper)
        val idView: TextView = view.findViewById(R.id.item_number)
        val contentView: TextView = view.findViewById(R.id.content)

        fun bind(item: OpenGLESLearningItem) {
            idView.text = item.id.toString()
            contentView.text = item.content
            wrapperView.setOnClickListener {
                it.findNavController().navigate(item.navigationActionId)
            }
        }

        override fun toString(): String {
            return super.toString() + " '" + contentView.text + "'"
        }
    }
}