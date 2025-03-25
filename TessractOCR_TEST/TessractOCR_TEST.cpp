#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <windows.h>  // Sleep() 함수 사용

int main()
{
	SetConsoleOutputCP(CP_UTF8); // UTF-8 출력 설정
	setvbuf(stdout, nullptr, _IOFBF, 1000); // 버퍼링 문제 방지

	tesseract::TessBaseAPI* api = new tesseract::TessBaseAPI();

	// ✅ Tesseract 초기화 확인
	if (api->Init(NULL, "kor")) {
		std::cerr << "Tesseract 초기화 실패!" << std::endl;
		return -1;
	}

	// ✅ 이미지 로드 확인 (최대 3회 재시도)
	Pix* image = nullptr;
	for (int i = 0; i < 3; i++) {
		//image = pixRead("D:/Project/MFC/TessractOCR_TEST/TessractOCR_TEST/x64/Debug/test.png");
		image = pixRead("D:/Project/MFC/CarPlateOCR/CarPlateOCR/x64/Debug/carNumberImage/temp.png");

	
		if (image) break;
		std::cerr << "이미지 로드 실패, 다시 시도 중... (" << i + 1 << "/3)" << std::endl;
		Sleep(100);  // 100ms 대기 후 다시 시도
	}

	if (!image) {
		std::cerr << "이미지를 불러오지 못했습니다. 프로그램을 종료합니다." << std::endl;
		return -1;
	}

	// ✅ OCR 수행
	api->SetImage(image);
	char* outText = api->GetUTF8Text();
	if (outText) {
		std::cout << "OCR output:\n" << outText << std::endl;
		std::cout.flush();  // 🚀 강제 플러시 추가
		delete[] outText;
	}
	else {
		std::cerr << "OCR 실패!" << std::endl;
	}

	// ✅ 리소스 해제
	api->End();
	delete api;
	pixDestroy(&image);

	return 0;
}
