#include "Operation.h"

void Add::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							*pixels[y*l->getWidth() + x] += k;
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {*p += k;});
			}
		}
	});
}

void Abs::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							(*pixels[y*l->getWidth() + x]).abs();
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {(*p).abs();});
			}
		}
	});
}

void BlackandWhite::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							(*pixels[y*l->getWidth() + x]).blackAndWhite();
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {(*p).blackAndWhite();});
			}
		}
	});
}

void Div::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							*pixels[y*l->getWidth() + x] /= k;
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {*p /= k;});
			}
		}
	});

}

void Inversion::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							(*pixels[y*l->getWidth() + x]).inverse();
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {(*p).inverse();});
			}
		}
	});
}

void InvertDiv::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							*pixels[y*l->getWidth() + x] /= k;
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {*p /= k;});
			}
		}
	});
}

void InvertSub::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							*pixels[y*l->getWidth() + x] = k - *pixels[y*l->getWidth() + x];
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {*p = k - *p;});
			}
		}
	});

}

void Log::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							(*pixels[y*l->getWidth() + x]).log();
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {(*p).log();});
			}
		}
	});
}

void Max::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							(*pixels[y*l->getWidth() + x]).max(k);
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {(*p).max(k);});
			}
		}
	});
}

void Min::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							(*pixels[y*l->getWidth() + x]).min(k);
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {(*p).min(k);});
			}
		}
	});
}

void Mul::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							*pixels[y*l->getWidth() + x] *= k;
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {*p *= k;});
			}
		}
	});

}

void Power::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							(*pixels[y*l->getWidth() + x]).power(k);
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {(*p).power(k);});
			}
		}
	});
}

void ShadesofGray::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							int avg = (*pixels[y*l->getWidth() + x]).avg();
							(*pixels[y*l->getWidth() + x]).setRed(avg);
							(*pixels[y*l->getWidth() + x]).setGreen(avg);
							(*pixels[y*l->getWidth() + x]).setBlue(avg);
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {
					int avg = (*p).avg();
					(*p).setRed(avg);
					(*p).setGreen(avg);
					(*p).setBlue(avg);
					(*p).setAlpha(avg);
				});
			}
		}
	});
}

void Sub::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							*(pixels[y*l->getWidth() + x]) -= k;
						}
					}
				});
			}
			else {
				std::vector<Pixel*> pixels = l->getPixels();
				std::for_each(pixels.begin(), pixels.end(), [this](Pixel* p) {*p -= k;});
			}
		}
	});

}

void Median::fun()
{
	std::vector<Layer*> layers = image->getLayers();
	std::for_each(layers.begin(), layers.end(), [this](Layer* l) {
		if (l->getActive()) {
			std::vector<Pixel*> pixels = l->getPixels();
			if (image->getSelectioin()) {
				std::vector<Rectangle> rectangle = image->getSelectioin()->getSelection();
				std::for_each(rectangle.begin(), rectangle.end(), [&](Rectangle r) {
					for (int y = r.getPosition().second;y < r.getPosition().second + r.getHeight();++y) {
						for (int x = r.getPosition().first;x < r.getPosition().first + r.getWidth();++x) {
							red.push_back(pixels[y*l->getWidth() + x]->getRed());
							green.push_back(pixels[y*l->getWidth() + x]->getGreen());
							blue.push_back(pixels[y*l->getWidth() + x]->getBlue());
							if (x - 1 > 0) {
								red.push_back(pixels[y*l->getWidth() + x - 1]->getRed());
								green.push_back(pixels[y*l->getWidth() + x - 1]->getGreen());
								blue.push_back(pixels[y*l->getWidth() + x - 1]->getBlue());
							}
							if (x + 1 < l->getWidth() - 1) {
								red.push_back(pixels[y*l->getWidth() + x + 1]->getRed());
								green.push_back(pixels[y*l->getWidth() + x + 1]->getGreen());
								blue.push_back(pixels[y*l->getWidth() + x + 1]->getBlue());
							}
							if (y + 1 < l->getHeight() - 1) {
								red.push_back(pixels[(y + 1)*l->getWidth() + x]->getRed());
								green.push_back(pixels[(y + 1)*l->getWidth() + x]->getGreen());
								blue.push_back(pixels[(y + 1)*l->getWidth() + x]->getBlue());
							}
							if (y - 1 > 0) {
								red.push_back(pixels[(y - 1)*l->getWidth() + x]->getRed());
								green.push_back(pixels[(y - 1)*l->getWidth() + x]->getGreen());
								blue.push_back(pixels[(y - 1)*l->getWidth() + x]->getBlue());
							}
							sort(red.begin(),red.end());
							sort(green.begin(),green.end());
							sort(blue.begin(),blue.end());
							pixels[y*l->getWidth() + x]->setRed(red.size() % 2 == 1 ? red[red.size() / 2] : (red[red.size() / 2] + red[red.size() / 2 - 1]) / 2);
							pixels[y*l->getWidth() + x]->setGreen(green.size() % 2 == 1 ? green[green.size() / 2] : (green[green.size() / 2] + green[green.size() / 2 - 1]) / 2);
							pixels[y*l->getWidth() + x]->setBlue(blue.size() % 2 == 1 ? blue[blue.size() / 2] : (blue[blue.size() / 2] + blue[blue.size() / 2 - 1]) / 2);
							red.clear();
							green.clear();
							blue.clear();
						}
					}
				});
			}
			else {
				for (int y = 0;y < l->getHeight();++y) {
					for (int x = 0;x < l->getWidth();++x) {
						red.push_back(pixels[y*l->getWidth() + x]->getRed());
						green.push_back(pixels[y*l->getWidth() + x]->getGreen());
						blue.push_back(pixels[y*l->getWidth() + x]->getBlue());
						if (x - 1 > 0) {
							red.push_back(pixels[y*l->getWidth() + x - 1]->getRed());
							green.push_back(pixels[y*l->getWidth() + x - 1]->getGreen());
							blue.push_back(pixels[y*l->getWidth() + x - 1]->getBlue());
						}
						if (x + 1 < l->getWidth() - 1) {
							red.push_back(pixels[y*l->getWidth() + x + 1]->getRed());
							green.push_back(pixels[y*l->getWidth() + x + 1]->getGreen());
							blue.push_back(pixels[y*l->getWidth() + x + 1]->getBlue());
						}
						if (y + 1 < l->getHeight() - 1) {
							red.push_back(pixels[(y + 1)*l->getWidth() + x]->getRed());
							green.push_back(pixels[(y + 1)*l->getWidth() + x]->getGreen());
							blue.push_back(pixels[(y + 1)*l->getWidth() + x]->getBlue());
						}
						if (y - 1 > 0) {
							red.push_back(pixels[(y - 1)*l->getWidth() + x]->getRed());
							green.push_back(pixels[(y - 1)*l->getWidth() + x]->getGreen());
							blue.push_back(pixels[(y - 1)*l->getWidth() + x]->getBlue());
						}
						sort(red.begin(), red.end());
						sort(green.begin(), green.end());
						sort(blue.begin(), blue.end());
						pixels[y*l->getWidth() + x]->setRed(red.size() % 2 == 1 ? red[red.size() / 2] : (red[red.size() / 2] + red[red.size() / 2 - 1]) / 2);
						pixels[y*l->getWidth() + x]->setGreen(green.size() % 2 == 1 ? green[green.size() / 2] : (green[green.size() / 2] + green[green.size() / 2 - 1]) / 2);
						pixels[y*l->getWidth() + x]->setBlue(blue.size() % 2 == 1 ? blue[blue.size() / 2] : (blue[blue.size() / 2] + blue[blue.size() / 2 - 1]) / 2);
						red.clear();
						green.clear();
						blue.clear();
					}
				}
			}
		}
	});

}
