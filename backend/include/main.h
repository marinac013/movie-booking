#include <drogon/drogon.h>

#include "domain/movie.h"
#include "domain/screening.h"
#include "domain/theater.h"
#include "repos/screening_repo.h"
#include "repos/booking_repo.h"
#include "services/booking_service.h"
#include "api/booking_controller.h"
#include "api/movie_controller.h"
#include "api/theater_controller.h"
#include "api/screening_controller.h"
#include "toml_wrapper.h"
#include "app_info.h"

#include <iostream>
#include <chrono>