using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Stage : MonoBehaviour
{
    public GameObject StageUI;
    public Text StageText;
    public static int mStage = 1;
    public static bool m_bStageOn = false;
    public float lasttime = 0f;
    public bool m_bTimeSave = true;
    void Start()
    {
        m_bStageOn = true;
        ActiveStage(m_bStageOn);
    }

    void Update()
    {
        StageCheck();
        if (m_bStageOn == true)
        {
            if (m_bTimeSave == true)
            {
                lasttime = Time.time;
                m_bTimeSave = false;
            }
            if (Time.time - lasttime >= 3)
            {
                lasttime = Time.time;
                m_bStageOn = false;
                m_bTimeSave = true;
                ActiveStage(m_bStageOn);
            }
        }
    }

    public void StageCheck()
    {
        if (GameManager.mScore >= mStage * 100 && m_bStageOn == false)
        {
            mStage++;
            m_bStageOn = true;
            UpdateStage();
            Field.AllDelete();
            ActiveStage(m_bStageOn);
            FindObjectOfType<obstacle>().CreateObstacle(mStage);
        }

    }
    public void UpdateStage()
    {
        StageText.text = "Stage" + mStage;
    }
    public void ActiveStage(bool look)
    {
        StageUI.SetActive(look);
    }

}
