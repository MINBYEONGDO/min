package com.example.myapplication;

import androidx.appcompat.app.AppCompatActivity;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Bundle;
import android.content.Context;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    @Override
    protected void onCreate(Bundle savedInstanceState) {
            super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
    protected void Box(int Score) {
//다이얼로그 객체 생성
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        //속성 지정
        String numStr = String.valueOf(Score);
        String Str1  = "종료하시겠습니까\n";
        String Str2  = "Score : ";
        System.out.println(numStr);
        builder.setTitle("종료");
        builder.setMessage("종료하시겠습니까");
        String result = Str1.concat(Str2);
        result = result.concat(numStr);
        builder.setMessage(result);

        //아이콘
        builder.setIcon(android.R.drawable.ic_dialog_alert);
        //예 버튼 눌렀을 때
        builder.setPositiveButton("예", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                Toast.makeText(getApplicationContext(), "우측버튼 클릭됨", Toast.LENGTH_LONG).show();
                android.os.Process.killProcess(android.os.Process.myPid());
                //텍스트 뷰 객체를 넣어줌..
            }
        });
        //예 버튼 눌렀을 때

        builder.setNegativeButton("아니오", new DialogInterface.OnClickListener()
        {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                //텍스트 뷰 객체를 넣어줌..
                Toast.makeText(getApplicationContext(), "좌측버튼 클릭됨", Toast.LENGTH_LONG).show();
            }
        });
        //만들어주기
        AlertDialog dialog = builder.create();
        dialog.show();
    }
}
