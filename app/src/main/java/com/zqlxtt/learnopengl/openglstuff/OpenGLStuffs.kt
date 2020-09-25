package com.zqlxtt.learnopengl.openglstuff

import com.zqlxtt.learnopengl.R
import java.util.ArrayList
import java.util.HashMap

/**
 * Helper class for providing sample content for user interfaces created by
 * Android template wizards.
 *
 * TODO: Replace all uses of this class before publishing your app.
 */
object OpenGLStuffs {

    /**
     * An array of sample (dummy) items.
     */
    val ITEMS: MutableList<OpenGLESLearningItem> = arrayListOf(
        OpenGLESLearningItem(
            1,
            "OpenGLES 环境初始化",
            R.id.action_openglStuffFragment_to_fragmentInitOpenGLES
        ),
        OpenGLESLearningItem(
            2,
            "OpenGLES 绘制三角形",
            R.id.action_openglStuffFragment_to_fragmentDrawTriangle
        )
    )

    /**
     * A dummy item representing a piece of content.
     */
    data class OpenGLESLearningItem(val id: Int, val content: String, val navigationActionId: Int) {
        override fun toString(): String = content
    }
}