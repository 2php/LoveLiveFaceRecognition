#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include <boost/filesystem.hpp>  
#include <iostream>

using namespace cv;

int get_filenames(const std::string& dir, std::vector<std::string>& filenames)
{
	namespace fs = boost::filesystem;
	fs::path path(dir);
	if (!fs::exists(path))
	{
		return -1;
	}

	fs::directory_iterator end_iter;
	for (fs::directory_iterator iter(path); iter != end_iter; ++iter)
	{
		if (fs::is_regular_file(iter->status()))
		{
			filenames.push_back(iter->path().string());
		}

		if (fs::is_directory(iter->status()))
		{
			get_filenames(iter->path().string(), filenames);
		}
	}
	return filenames.size();
}

Mat detectFace(Mat original, cv::CascadeClassifier haar_cascade)
{
	Mat gray;
	cvtColor(original, gray, CV_BGR2GRAY);
	std::vector< Rect_<int> > faces;
	haar_cascade.detectMultiScale(gray, faces, 1.1, 5, 0, Size(24, 24));
	if (faces.size()>0)
	{
		int size = 0;
		int seletect = 0;
		for (int i = 0; i < faces.size(); i++)
		{
			if (faces[i].width >= size)
			{
				seletect = i;
			}
		}
		Rect face_seletect = faces[seletect];
		Mat face = original(face_seletect);
		return face;
	}
	else
	{
		return Mat(0, 0, 0);
	}
}

std::vector<std::string> SplitString(const std::string& s, const std::string& c)
{
	std::vector<std::string> v;
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
	return v;
}

void builddataset()
{
	std::vector<std::string> filenames;
	get_filenames("D:\\FestivalCards", filenames);
	std::string fn_haar = std::string("lbpcascade_animeface.xml");
	cv::CascadeClassifier haar_cascade;
	haar_cascade.load(fn_haar);
	for (int i = 0; i < filenames.size(); i++)
	{
		Mat original = imread(filenames[i]);
		Mat face = detectFace(original, haar_cascade);
		if (face.cols == 0 || face.rows == 0)
		{
			continue;
		}
		boost::filesystem::path p(filenames[i]);
		std::vector<std::string> sArray = SplitString(p.parent_path().string(), "\\");
		std::string savedir = "D:\\Research\\LoveLiveFaceRecognition\\complete_data\\" + sArray[sArray.size() - 1];
		if (!boost::filesystem::exists(savedir))
		{
			boost::filesystem::create_directory(savedir);
		}
		Rect ROI = Rect(face.cols *0.1, face.rows*0.1, face.cols*0.8, face.rows*0.8);
		Mat saveImage = face(ROI);
		resize(saveImage, saveImage, Size(128, 128));
		if (!boost::filesystem::exists(savedir + "\\" + p.filename().string()))
		{
			imwrite(savedir + "\\" + p.filename().string(), saveImage);
		}
	}
}

int main()
{
	std::string mus[9] = { "Eli", "Hanayo", "Honoka", "Kotori", "Maki", "Nico", "Nozomi", "Rin", "Umi" };
	std::ofstream train("D:\\Research\\LoveLiveFaceRecognition\\label\\train.txt");
	std::ofstream val("D:\\Research\\LoveLiveFaceRecognition\\label\\val.txt");
	std::ofstream test("D:\\Research\\LoveLiveFaceRecognition\\label\\test.txt");
	for (int i = 0; i < 9; i++)
	{
		std::vector<std::string> filenames;
		get_filenames("D:\\Research\\LoveLiveFaceRecognition\\complete_data\\" + mus[i], filenames);
		srand((unsigned)time(NULL));
		for (int j = 0; j < filenames.size(); j++)
		{
			int prob = rand() % 100;
			if (prob<80)
			{
				train << filenames[j] << " " << i << std::endl;
			}
			else if (prob>=90)
			{
				val << filenames[j] << " " << i << std::endl;
			}
			else
			{
				test << filenames[j] << " " << i << std::endl;
			}
			boost::detail::Sleep(3);
		}
	}
	train.close();
	val.close();
	test.close();
	return 0;
}